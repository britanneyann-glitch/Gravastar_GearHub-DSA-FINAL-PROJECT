#ifndef GEAR_HUB_H
#define GEAR_HUB_H

#include "ProductCatalog.h"
#include "ProductBST.h"
#include "ShoppingCart.h"
#include "BrandCircle.h"
#include "UndoStack.h"
#include "CheckoutQueue.h"

class GearHub {
private:
    ProductCatalog catalog;
    ProductBST idIndex;
    ShoppingCart cart;
    BrandCircle brandShowcase;
    UndoStack undoHistory;
    CheckoutQueue checkoutLine;

    void loadSampleProducts();
    void rebuildIdIndex();
    void showCatalog() const;
    void filterByBrand() const;
    void searchByKeyword() const;
    void filterByPrice() const;
    void addToCart();
    void processCheckout();
    void undoLastCheckout();
    void showBrandBanners() const;
    void sortInventory() const;

public:
    GearHub();
    void run();
};

#endif
