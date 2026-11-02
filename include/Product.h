#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct Product {
    int id;
    std::string name;
    std::string category;
    std::string brand;
    double price;
    int stockQuantity;
};

#endif
