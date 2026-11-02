#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include "Product.h"
#include <vector>
#include <string>

void insertionSort(std::vector<Product>& items, const std::string& key);
void quickSort(std::vector<Product>& items, int low, int high, const std::string& key);
void displaySorted(const std::vector<Product>& items);

#endif
