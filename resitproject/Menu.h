#pragma once

#include "ItemList.h"
#include <string>
#include <vector>

class Menu : public ItemList
{
public:
    Menu(std::string fileName) : ItemList(fileName) {}; //inherits constructor of parent class

    void display(); //display the menu

    void displayMenu();
    std::shared_ptr<Item> chooseItem(int number);


private:
    ItemList itemList; //instance of ItemList to manage menu items
    std::string fileName; //file name for menu data "menu.csv"

    std::vector<std::shared_ptr<Item>> menuItems;
    void markTwoForOneAppetisers();
};