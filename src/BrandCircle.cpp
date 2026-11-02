#include "BrandCircle.h"
#include <iostream>

BrandCircle::BrandCircle() : tail(nullptr), count(0) {}
BrandCircle::~BrandCircle() {
    if (!tail) return;
    Node* head = tail->next;
    tail->next = nullptr;
    while (head) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

void BrandCircle::addBrand(const std::string& brand) {
    Node* node = new Node(brand);
    if (!tail) {
        tail = node;
        node->next = node;
    } else {
        node->next = tail->next;
        tail->next = node;
        tail = node;
    }
    ++count;
}

void BrandCircle::showCycle() const {
    if (!tail) {
        std::cout << "No partner brands are registered.\n";
        return;
    }
    Node* current = tail->next;
    std::cout << "\nPARTNER BRAND SHOWCASE (CIRCULAR LIST)\n";
    for (int i = 0; i < count; ++i) {
        std::cout << " -> " << current->brand;
        current = current->next;
    }
    std::cout << " -> back to " << tail->next->brand << "\n";
}
