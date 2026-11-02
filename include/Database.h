#ifndef DATABASE_H
#define DATABASE_H

#include "Product.h"
#include <memory>
#include <string>
#include <vector>

// Thin wrapper around libpqxx. The rest of the program never includes <pqxx>,
// so only Database.cpp depends on the PostgreSQL libraries.
class Database {
private:
    struct Impl;
    std::unique_ptr<Impl> impl;
    std::string error;
    bool connected;

public:
    Database();
    ~Database();
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    // Order of lookup: GEARHUB_DB_CONN environment variable, then the first
    // line of db.conf in the working folder, then a localhost default.
    static std::string defaultConnectionString();

    bool connect(const std::string& connectionString);
    bool isConnected() const;
    const std::string& lastError() const;

    bool initSchema();
    bool seedIfEmpty(const std::vector<Product>& products,
                     const std::vector<std::string>& brands);
    bool loadProducts(std::vector<Product>& out);
    bool loadBrands(std::vector<std::string>& out);

    // Each call runs in one transaction and writes a row to checkout_log.
    bool deductStock(int productId, int quantity, int& newStock);
    bool restoreStock(int productId, int quantity, int& newStock);
};

#endif
