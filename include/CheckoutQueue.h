#ifndef CHECKOUT_QUEUE_H
#define CHECKOUT_QUEUE_H

class CheckoutQueue {
private:
    struct Node {
        int productId;
        int quantity;
        Node* next;
        Node(int id, int qty) : productId(id), quantity(qty), next(nullptr) {}
    };
    Node* frontNode;
    Node* rearNode;

public:
    CheckoutQueue();
    ~CheckoutQueue();
    CheckoutQueue(const CheckoutQueue&) = delete;
    CheckoutQueue& operator=(const CheckoutQueue&) = delete;

    void enqueue(int productId, int quantity);
    bool dequeue(int& productId, int& quantity);
    bool empty() const;
    void clear();
};

#endif
