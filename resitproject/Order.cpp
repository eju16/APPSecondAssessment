#include "Order.h"
#include <iostream>
#include <iomanip>

Order::Order() {}

void Order::addItem(std::shared_ptr<Item> item)
{
    items.push_back(item);
    updateTotalPriceOnAdd(item); //updates the total price after adding item
}

void Order::removeItem(int index)
{
    //checks if index is valid
    if (index < 0 || index >= items.size()) 
    {
        std::cerr << "Invalid index." << std::endl;
        return;
    }

    //removes the item at the specified index
    auto itemToRemove = items[index];
    items.erase(items.begin() + index);

    //updates the total price after removing item
    updateTotalPriceOnRemove(itemToRemove);
}

void Order::displayOrder()
{
    if (items.empty())
    {
        std::cout << "Order is empty." << std::endl;
        return;
    }

    std::cout << "===========================================================================" << std::endl;

    std::cout << std::setw(5) << std::left << "No."
        << std::setw(25) << std::left << "Name"
        << std::setw(15) << std::left << "Type"
        << std::setw(10) << std::left << "Price (£)"
        << std::endl;

    int itemNumber = 1;
    for (const auto& item : items)
    {
        std::cout << std::setw(5) << std::left << itemNumber++
            << std::setw(25) << std::left << item->getName()
            << std::setw(15) << std::left << item->getType()
            << std::setw(10) << std::left << item->getPrice()
            << std::endl;
    }
    std::cout << "--------------------" << std::endl;
    std::cout << std::setw(45) << std::left << "Total Price (£)"
        << std::setw(10) << std::left << getTotalPrice()
        << std::endl;
    std::cout << "===========================================================================" << std::endl;
}

void Order::updateTotalPriceOnAdd(std::shared_ptr<Item> item)
{
    //updates total price normally
    totalPrice += item->getPrice();

    //2 for 1 appetiser logic
    /***
    * counts amount of two for ones
    * for every pair only one of the appetisers will count in the total price
    ***/
    if (isTwoForOneAppetiser(item)) 
    {
        int countTwoForOne = 0;
        for (const auto& it : items) 
        {
            if (isTwoForOneAppetiser(it)) 
            {
                countTwoForOne++;
            }
        }
        
        //if this is the second 2 for 1 appetiser added, adjust the total price
        if (countTwoForOne % 2 == 0) 
        {
            std::cout << std::endl;
            std::cout << "------------------------------------------" << std::endl;
            std::cout << "2-for-1 discount applied! Savings £" << item->getPrice() << std::endl;
            std::cout << "------------------------------------------" << std::endl;
            std::cout << std::endl;
            totalPrice -= item->getPrice();
        }
    }
}

void Order::updateTotalPriceOnRemove(std::shared_ptr<Item> item)
{
    //normal deduction of the price of the removed item from the total
    totalPrice -= item->getPrice();

    //2 for 1 appetiser logic
    if (isTwoForOneAppetiser(item)) 
    {
        int countTwoForOne = 0;
        for (const auto& it : items) 
        {
            if (isTwoForOneAppetiser(it)) 
            {
                countTwoForOne++;
            }
        }
        //if no other 2 for 1 appetiser found, adjust the total price
        //if there's a remainer 1 (odd no. of appetisers) 
        if (countTwoForOne % 2 == 1) 
        {
            totalPrice += item->getPrice();
        }
    }
}

double Order::getTotalPrice()
{
    return totalPrice;
}

int Order::getOrderSize()
{
    return items.size();
}

void Order::clearOrder()
{
    items.clear(); //clear all items from the order
    totalPrice = 0.0; //reset total price
}

//check if it is 2 for 1
bool Order::isTwoForOneAppetiser(std::shared_ptr<Item> item)
{
    auto appetiser = std::dynamic_pointer_cast<Appetiser>(item);
    return appetiser && appetiser->getTwoForOne();
}
