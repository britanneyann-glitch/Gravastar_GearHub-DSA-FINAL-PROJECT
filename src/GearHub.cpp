#include "GearHub.h"
#include "InputUtils.h"
#include "SearchAlgorithms.h"
#include "SortAlgorithms.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

GearHub::GearHub() { loadSampleProducts(); }

void GearHub::loadSampleProducts() {
    const Product samples[] = {
        {1001, "Astra Wireless Speaker", "Audio", "Gravastar", 5499.00, 12},
        {1002, "Mars Pro Speaker", "Audio", "Gravastar", 8999.00, 8},
        {2001, "Osmo Mobile SE", "Camera Gear", "DJI", 6999.00, 10},
        {2002, "Mini 4 Pro", "Drone", "DJI", 45999.00, 4},
        {3001, "K2 Mechanical Keyboard", "Keyboard", "Keychron", 4590.00, 15},
        {3002, "Q1 Pro Keyboard", "Keyboard", "Keychron", 9990.00, 7},
        {4001, "Insta360 GO 3S", "Camera", "Insta360", 23990.00, 5},
        {4002, "X4 Action Camera", "Camera", "Insta360", 28990.00, 6},
        {5001, "EcoFlow River 2", "Power Station", "EcoFlow", 12990.00, 9},
        {5002, "EcoFlow Delta 2", "Power Station", "EcoFlow", 54990.00, 3}
    };
    for (const Product& p : samples) catalog.add(p);

    const char* brands[] = {"Gravastar", "DJI", "Keychron", "Insta360", "EcoFlow"};
    for (const char* brand : brands) brandShowcase.addBrand(brand);
    rebuildIdIndex();
}

void GearHub::rebuildIdIndex() {
    idIndex.clear();
    for (int i = 0; i < catalog.size(); ++i) {
        const Product* p = catalog.get(i);
        if (p) idIndex.insert(p->id);
    }
}

void GearHub::showCatalog() const {
    std::cout << "\nCOMPLETE PRODUCT CATALOG\n";
    catalog.display();
}

void GearHub::filterByBrand() const {
    std::string brand = readText("Enter official partner brand: ");
    bool found = false;
    for (int i = 0; i < catalog.size(); ++i) {
        const Product* p = catalog.get(i);
        if (p && p->brand == brand) {
            std::cout << p->id << " | " << p->name << " | PHP "
                      << std::fixed << std::setprecision(2) << p->price
                      << " | Stock: " << p->stockQuantity << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "No products found for that brand. Brand names are case-sensitive.\n";
}

void GearHub::searchByKeyword() const {
    std::string keyword = readText("Enter product, category, or brand keyword: ");
    std::vector<Product> data;
    for (int i = 0; i < catalog.size(); ++i) data.push_back(*catalog.get(i));
    linearKeywordSearch(data, keyword);
}

void GearHub::filterByPrice() const {
    double minimum = readDouble("Minimum price (PHP): ");
    double maximum = readDouble("Maximum price (PHP): ");
    std::vector<Product> data;
    for (int i = 0; i < catalog.size(); ++i) data.push_back(*catalog.get(i));
    binaryPriceRangeSearch(data, minimum, maximum);
}

void GearHub::addToCart() {
    int id = readInt("Enter product ID: ");
    if (!idIndex.contains(id)) {
        std::cout << "Product ID does not exist in the BST index.\n";
        return;
    }
    Product* p = catalog.findById(id);
    if (!p) {
        std::cout << "Product record was not found.\n";
        return;
    }
    int quantity = readInt("Enter quantity: ");
    if (quantity <= 0 || quantity > p->stockQuantity) {
        std::cout << "Invalid quantity. Check available stock.\n";
        return;
    }
    cart.addItem(id, quantity);
    std::cout << quantity << " item(s) added to the shopping cart.\n";
    cart.display(catalog);
}

void GearHub::processCheckout() {
    if (cart.empty()) {
        std::cout << "Your cart is empty. Add an item first.\n";
        return;
    }
    // Transfer cart entries to the FIFO checkout queue.
    const std::vector<std::pair<int, int>> cartItems = cart.getItems();
    for (const auto& item : cartItems) {
        checkoutLine.enqueue(item.first, item.second);
    }
    cart.clear();

    int id, quantity;
    int processed = 0;
    while (checkoutLine.dequeue(id, quantity)) {
        Product* p = catalog.findById(id);
        if (!p || p->stockQuantity < quantity) {
            std::cout << "Order for product ID " << id << " could not be completed (stock changed).\n";
            continue;
        }
        p->stockQuantity -= quantity;
        undoHistory.push({id, quantity});
        std::cout << "Checked out: " << p->name << " x " << quantity
                  << ". Remaining stock: " << p->stockQuantity << "\n";
        ++processed;
    }
    std::cout << "Checkout completed. Processed cart lines: " << processed << "\n";
}

void GearHub::undoLastCheckout() {
    UndoRecord record;
    if (!undoHistory.pop(record)) {
        std::cout << "There is no checkout action to undo.\n";
        return;
    }
    Product* p = catalog.findById(record.productId);
    if (!p) {
        std::cout << "Undo failed because the product no longer exists.\n";
        return;
    }
    p->stockQuantity += record.quantity;
    std::cout << "UNDO SUCCESSFUL: Restored " << record.quantity
              << " unit(s) of " << p->name << ". Current stock: "
              << p->stockQuantity << "\n";
}

void GearHub::showBrandBanners() const { brandShowcase.showCycle(); }

void GearHub::sortInventory() const {
    std::cout << "\nSORT OPTIONS\n1. By Price (Insertion Sort)\n2. By Stock (Quick Sort)\n3. By Brand (Quick Sort)\n";
    int choice = readInt("Choose sorting method: ");
    std::string key;
    if (choice == 1) key = "price";
    else if (choice == 2) key = "stock";
    else if (choice == 3) key = "brand";
    else {
        std::cout << "Invalid sorting option.\n";
        return;
    }

    std::vector<Product> data;
    for (int i = 0; i < catalog.size(); ++i) data.push_back(*catalog.get(i));

    if (choice == 1) insertionSort(data, key);
    else quickSort(data, 0, static_cast<int>(data.size()) - 1, key);
    displaySorted(data);
}


void GearHub::run() {
    int choice;

    do {
        // Clear the terminal screen before showing the menu
        system("cls");

        std::cout << "\n============================================================\n"
                  << "       GRAVASTAR GEARHUB - E-COMMERCE SYSTEM (CS201)\n"
                  << "============================================================\n"
                  << "1. View Complete Catalog\n"
                  << "2. Filter Products by Official Brand\n"
                  << "3. Search Products by Keyword (Linear Search)\n"
                  << "4. Filter Products by Price Range (Binary Search)\n"
                  << "5. Add Item to Shopping Cart (Doubly Linked List)\n"
                  << "6. Process Customer Checkout Queue (FIFO Order Queue)\n"
                  << "7. Perform Admin Undo Action (LIFO Stack Pop)\n"
                  << "8. Display Partner Brand Banner Showcase (Circular List Cycle)\n"
                  << "9. Sort Inventory Display (By Price, Stock, or Brand)\n"
                  << "10. Exit\n"
                  << "============================================================\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                showCatalog();
                break;

            case 2:
                filterByBrand();
                break;

            case 3:
                searchByKeyword();
                break;

            case 4:
                filterByPrice();
                break;

            case 5:
                addToCart();
                break;

            case 6:
                processCheckout();
                break;

            case 7:
                undoLastCheckout();
                break;

            case 8:
                showBrandBanners();
                break;

            case 9:
                sortInventory();
                break;

            case 10:
                std::cout << "\nThank you for visiting Gravastar GearHub!\n";
                break;

            default:
                std::cout << "\nInvalid choice. Select a number from 1 to 10.\n";
        }

        // Wait before clearing the result
        if (choice != 10) {
            std::cout << "\nPress ENTER to return to the main menu...";
            std::string pause;
            std::getline(std::cin, pause);
        }

    } while (choice != 10);
}
