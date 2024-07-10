#pragma once

#include "ItemList.h"
#include "Appetiser.h"
#include <vector>
#include <memory>

class Order {
public:
    Order();

    void addItem(std::shared_ptr<Item> item);
    void removeItem(int index);
    void displayOrder();
    double getTotalPrice();
    int getOrderSize();
    void clearOrder();

private:
    std::vector<std::shared_ptr<Item>> items;
    double totalPrice = 0.0;

    void updateTotalPriceOnAdd(std::shared_ptr<Item> item);
    void updateTotalPriceOnRemove(std::shared_ptr<Item> item);
    bool isTwoForOneAppetiser(std::shared_ptr<Item> item);
};
