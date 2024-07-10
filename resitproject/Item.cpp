#include "Item.h"

Item::Item(std::string name, double price, int calories) : name(name), price(price), calories(calories) {}

Item::~Item() {}

std::string Item::getName()
{
    return name;
}

double Item::getPrice()
{
    return price;
}

int Item::getCalories() 
{
    return calories;
}

