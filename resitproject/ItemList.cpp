#include "ItemList.h"

ItemList::ItemList(std::string fileName)
{
    _csvMenu = readItemListFile(fileName); //constructor uses readItemListFile method
}

std::vector<std::vector<std::string>> ItemList::readItemListFile(std::string fileName) 
{
    std::ifstream fin(fileName);
    std::vector<std::vector<std::string>> itemList;
    std::string line;

    if (!fin.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return itemList;
    }

    while (getline(fin, line)) 
    {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (getline(ss, cell, ',')) 
        {
            row.push_back(cell);
        }

        itemList.push_back(row);
    }

    fin.close();
    return itemList;
}

//get items by their category a/b/m
std::vector<std::vector<std::string>> ItemList::getItemsByCategory(std::vector<std::vector<std::string>> itemList, std::string category) 
{
    std::vector<std::vector<std::string>> result;
    for (auto item : itemList) 
    {
        if (!item.empty() && item[0] == category) 
        {
            result.push_back(item);
        }
    }
    return result;
}


std::shared_ptr<Item> ItemList::getItemByNumber(int number)
{
    if (number >= 1 && number <= items.size()) //checks it is within range
    {
        return items[number - 1]; //since vector is based on zero
    }
    else 
    {
        return nullptr;
    }
}

std::shared_ptr<Item> ItemList::createItem(ItemType type, std::vector<std::string> itemData) {
    std::shared_ptr<Item> item;

    switch (type)
    {
    case ItemType::Appetiser:
        item = std::make_shared<Appetiser>(
            itemData[1],
            std::stod(itemData[2]),
            std::stoi(itemData[3]),
            itemData[4] == "y", //shareable
            itemData[5] == "y"  //twoForOne
        );
        break;

    case ItemType::MainCourse:
        item = std::make_shared<MainCourse>(
            itemData[1],
            std::stod(itemData[2]),
            std::stoi(itemData[3])
        );
        break;

    case ItemType::Beverage:
        item = std::make_shared<Beverage>(
            itemData[1],
            std::stod(itemData[2]),
            std::stoi(itemData[3]),
            std::stod(itemData[6]), //volume
            std::stod(itemData[7]) //abv
        );
        break;

    default:
        //handles unsupported item types or throws an error
        throw std::invalid_argument("Unsupported item type");
    }

    return item;
}