# Gravastar GearHub

A console-based Brand-Affiliated E-Commerce Inventory and Search System in C++17.

## Main menu
The program follows the exact 10 menu operations specified in the DSA Final Output:
1. View Complete Catalog
2. Filter Products by Official Brand
3. Search Products by Keyword (Linear Search)
4. Filter Products by Price Range (Binary Search)
5. Add Item to Shopping Cart (Doubly Linked List Navigation)
6. Process Customer Checkout Queue (FIFO Order Queue)
7. Perform Admin Undo Action (LIFO Stack Pop)
8. Display Partner Brand Banner Showcase (Circular List Cycle)
9. Sort Inventory Display (By Price, Stock, or Brand)
10. Exit

## Lab integration
- Lab 1: Dynamic allocation and resizing of the product catalog array.
- Lab 2: Doubly linked list for the shopping cart.
- Lab 3: Circular linked list for cycling through partner brand names.
- Lab 4: Linked stack for undoing the most recent checkout stock deduction.
- Lab 5: Linked queue for FIFO checkout processing.
- Lab 6: Binary Search Tree index for product ID lookup.
- Lab 7: Linear keyword search and binary search boundaries for price ranges.
- Lab 8: Insertion Sort and Quick Sort for inventory views.

## Partner brand sample data
Gravastar, DJI, Keychron, Insta360, and EcoFlow. Product details, prices, and quantities are sample classroom data, not live store inventory or a claim of official commercial partnership.

## Compile on Windows PowerShell (g++)
Open PowerShell in this folder and run:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp GearHub.cpp ProductCatalog.cpp ProductBST.cpp ShoppingCart.cpp BrandCircle.cpp UndoStack.cpp CheckoutQueue.cpp SearchAlgorithms.cpp SortAlgorithms.cpp InputUtils.cpp -o gearhub.exe
.\gearhub.exe
```

Compile all `.cpp` files together. Do not compile `main.cpp` alone.

## Notes
This is a classroom console simulation. It does not connect to a database, process real payments, or access live inventory. The checkout queue updates the in-memory stock only while the program is running.
