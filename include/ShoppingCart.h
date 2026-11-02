#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include "Product.h"
#include <vector>
#include <utility>

class ShoppingCart {
private:
    struct Node {
        int productId;
        int quantity;
        Node* prev;
        Node* next;
        Node(int id, int qty) : productId(id), quantity(qty), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;

public:
    ShoppingCart();
    ~ShoppingCart();
    ShoppingCart(const ShoppingCart&) = delete;
    ShoppingCart& operator=(const ShoppingCart&) = delete;

    void addItem(int productId, int quantity);
    bool empty() const;
    void display(const class ProductCatalog& catalog) const;
    void clear();
    std::vector<std::pair<int, int>> getItems() const;
};

#endif
