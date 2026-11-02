#include "CheckoutQueue.h"

CheckoutQueue::CheckoutQueue() : frontNode(nullptr), rearNode(nullptr) {}
CheckoutQueue::~CheckoutQueue() { clear(); }

void CheckoutQueue::enqueue(int productId, int quantity) {
    Node* node = new Node(productId, quantity);
    if (rearNode) rearNode->next = node;
    else frontNode = node;
    rearNode = node;
}

bool CheckoutQueue::dequeue(int& productId, int& quantity) {
    if (!frontNode) return false;
    Node* oldFront = frontNode;
    productId = oldFront->productId;
    quantity = oldFront->quantity;
    frontNode = oldFront->next;
    if (!frontNode) rearNode = nullptr;
    delete oldFront;
    return true;
}

bool CheckoutQueue::empty() const { return frontNode == nullptr; }

void CheckoutQueue::clear() {
    int id, qty;
    while (dequeue(id, qty)) {}
}
