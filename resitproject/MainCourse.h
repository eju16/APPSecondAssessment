#pragma once

#include "Item.h"

class MainCourse : public Item {
public:
    MainCourse(std::string name, double price, int calories);
    std::string getType() override;

private:
    std::string type = "m";
    //no other specific attributes to this class
};
