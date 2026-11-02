#include "SearchAlgorithms.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iomanip>

static std::string lowerText(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return value;
}

void linearKeywordSearch(const std::vector<Product>& products, const std::string& keyword) {
    const std::string target = lowerText(keyword);
    bool found = false;
    std::cout << "\nLINEAR KEYWORD SEARCH RESULTS\n";
    for (const Product& p : products) {
        if (lowerText(p.name).find(target) != std::string::npos ||
            lowerText(p.category).find(target) != std::string::npos ||
            lowerText(p.brand).find(target) != std::string::npos) {
            std::cout << p.id << " | " << p.name << " | " << p.brand
                      << " | PHP " << std::fixed << std::setprecision(2) << p.price
                      << " | Stock: " << p.stockQuantity << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "No matching product found.\n";
}

void binaryPriceRangeSearch(const std::vector<Product>& products, double minimum, double maximum) {
    if (minimum > maximum) {
        std::cout << "Minimum price cannot be greater than maximum price.\n";
        return;
    }
    std::vector<Product> sorted = products;
    std::sort(sorted.begin(), sorted.end(),
        [](const Product& a, const Product& b) { return a.price < b.price; });

    // Binary search locates the first product whose price is >= minimum.
    int low = 0, high = static_cast<int>(sorted.size());
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (sorted[mid].price < minimum) low = mid + 1;
        else high = mid;
    }
    int start = low;

    // Binary search locates the first product whose price is > maximum.
    low = 0;
    high = static_cast<int>(sorted.size());
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (sorted[mid].price <= maximum) low = mid + 1;
        else high = mid;
    }
    int end = low;

    std::cout << "\nPRODUCTS WITHIN PHP " << minimum << " TO PHP " << maximum << "\n";
    if (start == end) {
        std::cout << "No products found in this price range.\n";
        return;
    }
    for (int i = start; i < end; ++i)
        std::cout << sorted[i].name << " | " << sorted[i].brand
                  << " | PHP " << std::fixed << std::setprecision(2) << sorted[i].price << "\n";
}

std::vector<Product> catalogToVector(const class ProductCatalog& catalog);
