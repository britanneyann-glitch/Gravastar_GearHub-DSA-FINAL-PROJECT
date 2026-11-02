#ifndef PRODUCT_CATALOG_H
#define PRODUCT_CATALOG_H

#include "Product.h"
#include <string>

class ProductCatalog {
private:
    Product* items;
    int count;
    int capacity;
    void resize(int newCapacity);

public:
    ProductCatalog();
    ~ProductCatalog();
    ProductCatalog(const ProductCatalog&) = delete;
    ProductCatalog& operator=(const ProductCatalog&) = delete;

    void add(const Product& product);
    int size() const;
    Product* get(int index);
    const Product* get(int index) const;
    Product* findById(int id);
    const Product* findById(int id) const;
    void display() const;
};

#endif
