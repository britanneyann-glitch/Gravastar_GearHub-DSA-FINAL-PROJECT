#ifndef BRAND_CIRCLE_H
#define BRAND_CIRCLE_H

#include <string>
#include <vector>

class BrandCircle {
private:
    struct Node {
        std::string brand;
        Node* next;
        explicit Node(const std::string& value) : brand(value), next(nullptr) {}
    };
    Node* tail;
    int count;

public:
    BrandCircle();
    ~BrandCircle();
    BrandCircle(const BrandCircle&) = delete;
    BrandCircle& operator=(const BrandCircle&) = delete;

    void addBrand(const std::string& brand);
    void showCycle() const;
};

#endif
