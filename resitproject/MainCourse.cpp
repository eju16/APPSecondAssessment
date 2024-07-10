#include "MainCourse.h"

MainCourse::MainCourse(std::string name, double price, int calories) : Item(name, price, calories) {}

//main course has no other specific item details

std::string MainCourse::getType() 
{
    return "m";
}