#include "ProductBST.h"

ProductBST::ProductBST() : root(nullptr) {}
ProductBST::~ProductBST() { clear(); }

ProductBST::Node* ProductBST::insertNode(Node* node, int id) {
    if (!node) return new Node(id);
    if (id < node->id) node->left = insertNode(node->left, id);
    else if (id > node->id) node->right = insertNode(node->right, id);
    return node;
}

const ProductBST::Node* ProductBST::searchNode(const Node* node, int id) const {
    if (!node || node->id == id) return node;
    if (id < node->id) return searchNode(node->left, id);
    return searchNode(node->right, id);
}

void ProductBST::insert(int id) { root = insertNode(root, id); }
bool ProductBST::contains(int id) const { return searchNode(root, id) != nullptr; }

void ProductBST::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void ProductBST::clear() {
    clear(root);
    root = nullptr;
}
