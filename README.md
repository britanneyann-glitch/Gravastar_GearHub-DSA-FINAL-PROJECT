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

## PostgreSQL backend
Products, brands, and stock levels are stored in PostgreSQL through libpqxx. At startup the program loads them into the same in-memory structures used before (dynamic array, BST index, circular brand list), so the search, sort, cart, queue, and undo code still works on the data structures. Checkout and undo write the stock change to the database in a transaction and add a row to `checkout_log`.

If the database cannot be reached, the program prints the error and runs in offline mode with the built-in sample data (nothing is saved).

### One-time setup
1. Create an empty database (the program creates the tables and sample rows itself on first run):
   ```
   psql -U postgres -c "CREATE DATABASE gearhub;"
   ```
2. Copy `db.conf.example` to `db.conf` and put your real password in it. `db.conf` is git-ignored. Alternatively, set the `GEARHUB_DB_CONN` environment variable to the same one-line connection string.
3. Install the libraries in the MSYS2 MinGW64 shell if you have not yet: `pacman -S mingw-w64-x86_64-libpqxx`

`sql/schema.sql` holds the same table definitions if you want to create them by hand.

## Build (MSYS2 MinGW64 shell)
```
make
./gearhub.exe
```
Or without make:
```
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o gearhub.exe -lpqxx -lpq
```
Run `gearhub.exe` from the folder that contains `db.conf`. If you run it outside the MSYS2 shell, add `C:\msys64\mingw64\bin` to PATH so the libpq and libpqxx DLLs are found.

## Notes
This is a classroom console simulation. It does not process real payments or access live inventory. Checkout and undo update stock in PostgreSQL when the database is connected. The undo stack itself lives in memory, so undo history is cleared when the program exits.
