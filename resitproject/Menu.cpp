#include "Menu.h"
#include <iostream>
#include <iomanip> //for std::setw (better formatting for outputted text)

//uses constructor from ItemList super class


void Menu::display()
{
    //counter for item numbers (the numbers will help when inputting item to an order)
    int itemNumber = 1;

    //column headers with adjusted spacing for better readability
    std::cout << std::setw(5) << std::left << "No."
        << std::setw(15) << std::left << "Type"
        << std::setw(25) << std::left << "Name"
        << std::setw(10) << std::left << "Price £"
        << std::setw(12) << std::left << "Calories"
        << std::setw(12) << std::left << "Shareable"
        << std::setw(8) << std::left << "2-4-1"
        << std::setw(15) << std::left << "Volume (ml)"
        << std::setw(15) << std::left << "ABV (%)" << std::endl;

    for (auto item : _csvMenu) {
        //checks if there's any empty fields, not all menu items have column values that apply to the item
        //columns that may be empty marked by "optional"
        if (!item[0].empty() && !item[1].empty() && !item[2].empty()) {
            std::cout << std::setw(5) << std::left << itemNumber++ //item number
                << std::setw(15) << std::left << item[0] //type
                << std::setw(25) << std::left << item[1] //name
                << std::setw(10) << std::left << item[2] //price
                << std::setw(12) << std::left << (item.size() > 3 ? item[3] : "") //calories (optional)
                << std::setw(12) << std::left << (item.size() > 4 ? (item[4] == "y" ? "Yes" : "No") : "") //shareable (optional)
                << std::setw(8) << std::left << (item.size() > 5 ? (item[5] == "y" ? "Yes" : "No") : "") //2 for 1 (optional)
                << std::setw(15) << std::left << (item.size() > 6 ? item[6] : "") //volume (optional)
                << std::setw(15) << std::left << (item.size() > 7 ? item[7] : "") << std::endl; //ABV (optional)
        }
        else {
            std::cerr << "Error: Incomplete data for menu item." << std::endl;
        }
    }
}


//makes item based on item from the menu using the inputted number
std::shared_ptr<Item> Menu::chooseItem(int number)
{
    if (number >= 1 && number <= _csvMenu.size())
    {
        char category = _csvMenu[number - 1][0][0];
        std::string name = _csvMenu[number - 1][1];
        double price = std::stod(_csvMenu[number - 1][2]);
        int calories = (_csvMenu[number - 1].size() > 3) ? std::stoi(_csvMenu[number - 1][3]) : 0;

        std::shared_ptr<Item> item;

        switch (category)
        {
        case 'a': //appetiser
            item = std::make_shared<Appetiser>(
                name,
                price,
                calories,
                (_csvMenu[number - 1].size() > 4 && _csvMenu[number - 1][4] == "y"),
                (_csvMenu[number - 1].size() > 5 && _csvMenu[number - 1][5] == "y")
            );
            break;

        case 'm': //main course
            item = std::make_shared<MainCourse>(name, price, calories);
            break;

        case 'b': //beverage
            if (_csvMenu[number - 1].size() > 6 && _csvMenu[number - 1].size() > 7)
            {
                double volume = std::stod(_csvMenu[number - 1][6]);
                double abv = std::stod(_csvMenu[number - 1][7]);
                item = std::make_shared<Beverage>(name, price, calories, volume, abv);
            }
            else
            {
                item = std::make_shared<Beverage>(name, price, calories, 0.0, 0.0);
            }
            break;

            //error handling for categories not a/b/m
        default:
            std::cerr << "Unknown item category." << std::endl;
            break;
        }
        return item;
    }
    else
    {
        std::cerr << "Invalid item number." << std::endl;
        return nullptr;
    }
}

