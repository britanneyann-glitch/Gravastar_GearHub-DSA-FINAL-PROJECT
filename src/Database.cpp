#include "Database.h"
#include <pqxx/pqxx>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iomanip>
#include <sstream>

struct Database::Impl {
    std::unique_ptr<pqxx::connection> conn;
};

Database::Database() : impl(new Impl), connected(false) {}

Database::~Database() = default;

std::string Database::defaultConnectionString() {
    if (const char* env = std::getenv("GEARHUB_DB_CONN")) {
        if (*env) return env;
    }
    std::ifstream file("db.conf");
    std::string line;
    if (file && std::getline(file, line)) {
        // Strip a trailing carriage return from Windows line endings.
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) line.pop_back();
        if (!line.empty()) return line;
    }
    return "host=localhost port=5432 dbname=gearhub user=postgres";
}

bool Database::connect(const std::string& connectionString) {
    try {
        impl->conn = std::make_unique<pqxx::connection>(connectionString);
        connected = impl->conn->is_open();
        if (!connected) error = "Connection could not be opened.";
    } catch (const std::exception& e) {
        error = e.what();
        connected = false;
        impl->conn.reset();
    }
    return connected;
}

bool Database::isConnected() const { return connected; }

const std::string& Database::lastError() const { return error; }

bool Database::initSchema() {
    if (!connected) return false;
    try {
        pqxx::work tx{*impl->conn};
        tx.exec("CREATE TABLE IF NOT EXISTS brands ("
                "id SERIAL PRIMARY KEY, "
                "name VARCHAR(50) NOT NULL UNIQUE)");
        tx.exec("CREATE TABLE IF NOT EXISTS products ("
                "id INTEGER PRIMARY KEY, "
                "name VARCHAR(100) NOT NULL, "
                "category VARCHAR(50) NOT NULL, "
                "brand VARCHAR(50) NOT NULL REFERENCES brands(name), "
                "price NUMERIC(12,2) NOT NULL CHECK (price >= 0), "
                "stock_quantity INTEGER NOT NULL CHECK (stock_quantity >= 0))");
        tx.exec("CREATE TABLE IF NOT EXISTS checkout_log ("
                "id SERIAL PRIMARY KEY, "
                "product_id INTEGER NOT NULL REFERENCES products(id), "
                "quantity INTEGER NOT NULL CHECK (quantity > 0), "
                "action VARCHAR(10) NOT NULL CHECK (action IN ('CHECKOUT', 'UNDO')), "
                "created_at TIMESTAMPTZ NOT NULL DEFAULT now())");
        tx.commit();
        return true;
    } catch (const std::exception& e) {
        error = e.what();
        return false;
    }
}

bool Database::seedIfEmpty(const std::vector<Product>& products,
                           const std::vector<std::string>& brands) {
    if (!connected) return false;
    try {
        pqxx::work tx{*impl->conn};
        pqxx::result count = tx.exec("SELECT COUNT(*) FROM products");
        if (count[0][0].as<long long>() > 0) return true;  // already has data

        for (const std::string& brand : brands) {
            tx.exec("INSERT INTO brands (name) VALUES (" + tx.quote(brand) +
                    ") ON CONFLICT (name) DO NOTHING");
        }
        for (const Product& p : products) {
            std::ostringstream price;
            price << std::fixed << std::setprecision(2) << p.price;
            tx.exec("INSERT INTO products (id, name, category, brand, price, stock_quantity) VALUES (" +
                    std::to_string(p.id) + ", " + tx.quote(p.name) + ", " +
                    tx.quote(p.category) + ", " + tx.quote(p.brand) + ", " +
                    price.str() + ", " + std::to_string(p.stockQuantity) + ")");
        }
        tx.commit();
        return true;
    } catch (const std::exception& e) {
        error = e.what();
        return false;
    }
}

bool Database::loadProducts(std::vector<Product>& out) {
    if (!connected) return false;
    try {
        pqxx::work tx{*impl->conn};
        pqxx::result rows = tx.exec(
            "SELECT id, name, category, brand, price::float8, stock_quantity "
            "FROM products ORDER BY id");
        out.clear();
        for (const auto& row : rows) {
            Product p;
            p.id = row[0].as<int>();
            p.name = row[1].as<std::string>();
            p.category = row[2].as<std::string>();
            p.brand = row[3].as<std::string>();
            p.price = row[4].as<double>();
            p.stockQuantity = row[5].as<int>();
            out.push_back(p);
        }
        tx.commit();
        return true;
    } catch (const std::exception& e) {
        error = e.what();
        return false;
    }
}

bool Database::loadBrands(std::vector<std::string>& out) {
    if (!connected) return false;
    try {
        pqxx::work tx{*impl->conn};
        pqxx::result rows = tx.exec("SELECT name FROM brands ORDER BY id");
        out.clear();
        for (const auto& row : rows) out.push_back(row[0].as<std::string>());
        tx.commit();
        return true;
    } catch (const std::exception& e) {
        error = e.what();
        return false;
    }
}

bool Database::deductStock(int productId, int quantity, int& newStock) {
    if (!connected) return false;
    try {
        pqxx::work tx{*impl->conn};
        // The stock check and the update happen in one statement, so two
        // sessions cannot both take the last unit.
        pqxx::result r = tx.exec(
            "UPDATE products SET stock_quantity = stock_quantity - " + std::to_string(quantity) +
            " WHERE id = " + std::to_string(productId) +
            " AND stock_quantity >= " + std::to_string(quantity) +
            " RETURNING stock_quantity");
        if (r.empty()) {
            error = "Product not found or not enough stock in the database.";
            return false;
        }
        newStock = r[0][0].as<int>();
        tx.exec("INSERT INTO checkout_log (product_id, quantity, action) VALUES (" +
                std::to_string(productId) + ", " + std::to_string(quantity) + ", 'CHECKOUT')");
        tx.commit();
        return true;
    } catch (const std::exception& e) {
        error = e.what();
        return false;
    }
}

bool Database::restoreStock(int productId, int quantity, int& newStock) {
    if (!connected) return false;
    try {
        pqxx::work tx{*impl->conn};
        pqxx::result r = tx.exec(
            "UPDATE products SET stock_quantity = stock_quantity + " + std::to_string(quantity) +
            " WHERE id = " + std::to_string(productId) +
            " RETURNING stock_quantity");
        if (r.empty()) {
            error = "Product not found in the database.";
            return false;
        }
        newStock = r[0][0].as<int>();
        tx.exec("INSERT INTO checkout_log (product_id, quantity, action) VALUES (" +
                std::to_string(productId) + ", " + std::to_string(quantity) + ", 'UNDO')");
        tx.commit();
        return true;
    } catch (const std::exception& e) {
        error = e.what();
        return false;
    }
}
