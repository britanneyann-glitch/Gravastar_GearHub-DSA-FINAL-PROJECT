#ifndef PRODUCT_BST_H
#define PRODUCT_BST_H

#include "Product.h"

class ProductBST {
private:
    struct Node {
        int id;
        Node* left;
        Node* right;
        explicit Node(int value) : id(value), left(nullptr), right(nullptr) {}
    };
    Node* root;
    Node* insertNode(Node* node, int id);
    const Node* searchNode(const Node* node, int id) const;
    void clear(Node* node);

public:
    ProductBST();
    ~ProductBST();
    ProductBST(const ProductBST&) = delete;
    ProductBST& operator=(const ProductBST&) = delete;

    void insert(int id);
    bool contains(int id) const;
    void clear();
};

#endif
