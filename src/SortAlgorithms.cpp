#include "SortAlgorithms.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iomanip>

static std::string lowerValue(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return value;
}

static bool comesBefore(const Product& a, const Product& b, const std::string& key) {
    if (key == "price") return a.price < b.price;
    if (key == "stock") return a.stockQuantity < b.stockQuantity;
    return lowerValue(a.brand) < lowerValue(b.brand);
}

void insertionSort(std::vector<Product>& items, const std::string& key) {
    for (std::size_t i = 1; i < items.size(); ++i) {
        Product current = items[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && comesBefore(current, items[j], key)) {
            items[j + 1] = items[j];
            --j;
        }
        items[j + 1] = current;
    }
}

static int partitionItems(std::vector<Product>& items, int low, int high, const std::string& key) {
    Product pivot = items[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (comesBefore(items[j], pivot, key)) {
            ++i;
            std::swap(items[i], items[j]);
        }
    }
    std::swap(items[i + 1], items[high]);
    return i + 1;
}

void quickSort(std::vector<Product>& items, int low, int high, const std::string& key) {
    if (low < high) {
        int pivot = partitionItems(items, low, high, key);
        quickSort(items, low, pivot - 1, key);
        quickSort(items, pivot + 1, high, key);
    }
}

void displaySorted(const std::vector<Product>& items) {
    if (items.empty()) {
        std::cout << "No products to display.\n";
        return;
    }
    std::cout << "\nSORTED INVENTORY\n";
    for (const Product& p : items)
        std::cout << p.id << " | " << p.name << " | " << p.brand
                  << " | PHP " << std::fixed << std::setprecision(2) << p.price
                  << " | Stock: " << p.stockQuantity << "\n";
}
