#include "ShoppingCart.h"
#include "ProductCatalog.h"
#include <iostream>
#include <iomanip>

ShoppingCart::ShoppingCart() : head(nullptr), tail(nullptr) {}
ShoppingCart::~ShoppingCart() { clear(); }

void ShoppingCart::addItem(int productId, int quantity) {
    for (Node* cur = head; cur; cur = cur->next) {
        if (cur->productId == productId) {
            cur->quantity += quantity;
            return;
        }
    }
    Node* node = new Node(productId, quantity);
    node->prev = tail;
    if (tail) tail->next = node;
    else head = node;
    tail = node;
}

bool ShoppingCart::empty() const { return head == nullptr; }

void ShoppingCart::display(const ProductCatalog& catalog) const {
    if (empty()) {
        std::cout << "Your shopping cart is empty.\n";
        return;
    }
    double total = 0;
    std::cout << "\nSHOPPING CART\n";
    for (Node* cur = head; cur; cur = cur->next) {
        const Product* p = catalog.findById(cur->productId);
        if (!p) continue;
        double subtotal = p->price * cur->quantity;
        total += subtotal;
        std::cout << p->name << " x " << cur->quantity
                  << " = PHP " << std::fixed << std::setprecision(2) << subtotal << "\n";
    }
    std::cout << "Cart total: PHP " << total << "\n";
}

void ShoppingCart::clear() {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
}

std::vector<std::pair<int, int>> ShoppingCart::getItems() const {
    std::vector<std::pair<int, int>> result;
    for (Node* cur = head; cur; cur = cur->next)
        result.push_back({cur->productId, cur->quantity});
    return result;
}
