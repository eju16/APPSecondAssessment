#pragma once

#include "Item.h"
#include "ItemType.h"
#include "Appetiser.h"
#include "MainCourse.h"
#include "Beverage.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

class ItemList {
public:
    ItemList() = default;
    ItemList(std::string fileName);

    std::vector<std::vector<std::string>> readItemListFile(std::string fileName);
    std::vector<std::vector<std::string>> getItemsByCategory(std::vector<std::vector<std::string>> itemList, std::string category);

    //void displayMenu();
    std::shared_ptr<Item> getItemByNumber(int number);

    std::shared_ptr<Item> createItem(ItemType type, std::vector<std::string> itemData); //create item instances based on their category

protected:
    std::vector<std::vector<std::string>> _csvMenu;

private:
    std::vector<std::vector<std::string>> itemList;
    std::vector<std::shared_ptr<Item>> items;
};
