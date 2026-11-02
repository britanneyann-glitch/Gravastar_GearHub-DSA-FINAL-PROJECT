#include "InputUtils.h"
#include <iostream>
#include <limits>
#include <sstream>

int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        int value;
        char extra;
        if (ss >> value && !(ss >> extra)) return value;
        std::cout << "Invalid input. Please enter a whole number.\n";
    }
}

double readDouble(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        double value;
        char extra;
        if (ss >> value && !(ss >> extra) && value >= 0) return value;
        std::cout << "Invalid input. Enter a valid non-negative amount.\n";
    }
}

std::string readText(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);
        if (!value.empty()) return value;
        std::cout << "This field cannot be empty.\n";
    }
}
