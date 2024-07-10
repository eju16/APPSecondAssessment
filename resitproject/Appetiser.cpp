#include "Appetiser.h"

Appetiser::Appetiser(std::string name, double price, int calories, bool shareable, bool twoForOne)
    : Item(name, price, calories), shareable(shareable), twoForOne(twoForOne) {}

bool Appetiser::isShareable()
{
    return shareable;
}

bool Appetiser::getTwoForOne() //getter
{
    return twoForOne;
}

void Appetiser::setTwoForOne(bool value) //setter used to help pointer/flag when adding/removing 2 for 1 appetisers
{
    twoForOne = value;
}

std::string Appetiser::getType() //returns default 'a' for appetisers
{
    return type;
}

bool Appetiser::isTwoForOne()
{
    return twoForOne;
}