#include "ProductCatalog.h"
#include <iostream>
#include <iomanip>

ProductCatalog::ProductCatalog() : items(new Product[4]), count(0), capacity(4) {}

ProductCatalog::~ProductCatalog() {
    delete[] items;
}

void ProductCatalog::resize(int newCapacity) {
    Product* bigger = new Product[newCapacity];
    for (int i = 0; i < count; ++i) bigger[i] = items[i];
    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

void ProductCatalog::add(const Product& product) {
    if (count == capacity) resize(capacity * 2);
    items[count++] = product;
}

int ProductCatalog::size() const { return count; }

Product* ProductCatalog::get(int index) {
    return (index >= 0 && index < count) ? &items[index] : nullptr;
}

const Product* ProductCatalog::get(int index) const {
    return (index >= 0 && index < count) ? &items[index] : nullptr;
}

Product* ProductCatalog::findById(int id) {
    for (int i = 0; i < count; ++i)
        if (items[i].id == id) return &items[i];
    return nullptr;
}

const Product* ProductCatalog::findById(int id) const {
    for (int i = 0; i < count; ++i)
        if (items[i].id == id) return &items[i];
    return nullptr;
}

void ProductCatalog::display() const {
    if (count == 0) {
        std::cout << "The catalog is empty.\n";
        return;
    }
    std::cout << "\n" << std::left
              << std::setw(7) << "ID" << std::setw(24) << "PRODUCT"
              << std::setw(16) << "CATEGORY" << std::setw(14) << "BRAND"
              << std::right << std::setw(12) << "PRICE"
              << std::setw(9) << "STOCK" << "\n";
    std::cout << std::string(82, '-') << "\n";
    for (int i = 0; i < count; ++i) {
        const Product& p = items[i];
        std::cout << std::left << std::setw(7) << p.id
                  << std::setw(24) << p.name.substr(0, 22)
                  << std::setw(16) << p.category.substr(0, 14)
                  << std::setw(14) << p.brand.substr(0, 12)
                  << std::right << std::fixed << std::setprecision(2)
                  << std::setw(12) << p.price
                  << std::setw(9) << p.stockQuantity << "\n";
    }
}
