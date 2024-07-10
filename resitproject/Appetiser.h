#pragma once

#include "Item.h"

class Appetiser : public Item {
public:
    Appetiser(std::string name, double price, int calories, bool shareable, bool twoForOne);

    bool isShareable();

    bool getTwoForOne();
    void setTwoForOne(bool value);
    std::string getType() override;

    bool isTwoForOne();

private:
    bool shareable;
    bool twoForOne; // = false;
    std::string type = "a";
};
