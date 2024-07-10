#pragma once

#include "Item.h"

class Beverage : public Item {
public:
    Beverage(std::string name, double price, int calories, double volume, double abv);

    double getVolume();
    double getABV();

    std::string getType() override;

private:
    double volume; // in ml
    double abv;    // alcohol by volume percentage
    std::string type = "b";
};
