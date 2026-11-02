#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include "Product.h"
#include <vector>

void linearKeywordSearch(const std::vector<Product>& products, const std::string& keyword);
void binaryPriceRangeSearch(const std::vector<Product>& products, double minimum, double maximum);

#endif
