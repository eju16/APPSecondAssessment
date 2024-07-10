#include "Beverage.h"

Beverage::Beverage(std::string name, double price, int calories, double volume, double abv) : Item(name, price, calories), volume(volume), abv(abv) {}
//5 attributes

double Beverage::getVolume() 
{
    return volume;
}

double Beverage::getABV() 
{
    return abv;
}

std::string Beverage::getType()
{
    return type;
}
