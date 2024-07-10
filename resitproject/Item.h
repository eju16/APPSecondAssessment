#pragma once

#include "ItemType.h"
#include <string>

//superclass for appetiser, beverage, main course

class Item {
public:
    Item(std::string name, double price, int calories);
    virtual ~Item();

    std::string getName();
    double getPrice();
    int getCalories();
    virtual std::string getType() = 0;

    

private:
    std::string name;
    double price;
    int calories;
    std::string type;
};
