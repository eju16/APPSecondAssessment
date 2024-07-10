#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include "Order.h"
#include "ItemList.h"

#include <iostream>
#include <vector>
#include <cstring>
#include <limits>

using namespace std;

//crashes when remove is used to empty the list //more commented in remove scope
//char(163) for £ not working in terminal, shows as accented u

int main()
{
    std::cout << "Type 'help' to see list of commands." << std::endl;

    string userCommand;
    vector<string> parameters;

    //creating instances
    Menu menu("menu.csv");
    Order order;

    while (userCommand != "exit")
    {
        std::cout << "Enter command\n> ";
        getline(cin, userCommand);
        char* cstr = new char[userCommand.length() + 1];
        strcpy(cstr, userCommand.c_str());

        char* token;
        token = strtok(cstr, " ");

        parameters.clear(); //clear parameters vector before reusing

        while (token != NULL)
        {
            parameters.push_back(token);
            token = strtok(NULL, " ");
        }

        string command = parameters[0];

        //-------------------------------------------------------------
        //---------SHOW MENU OPTION
        if (command.compare("menu") == 0)
        {
            menu.display(); //displays the menu
        }
        //END OF SHOW MENU
        // 
        // 
        //-------------------------------------------------------------
        //---------REMOVE ITEM OPTION
        else if (command.compare("add") == 0)
        {
            //initial user information to explain
            std::cout << "Choose items to add to order (enter item numbers, 0 to finish)" << std::endl;
            int choice;
            while (true)
            {
                //message shown after initial explanation, lets user keep track of what they are currently doing
                std::cout << std::endl;
                std::cout << "*********-ADD ITEM-*********" << std::endl;
                std::cout << "Enter item no. or enter 0 to end" << std::endl << ">";
                std::cin >> choice;

                if (std::cin.fail()) //check for invalid inputs
                {
                    std::cin.clear(); //clear error state
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore invalid input
                    std::cout << "Invalid input. Please enter a number." << std::endl;
                    continue;
                }

                if (choice == 0)
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear the input
                    std::cout << std::endl;
                    //std::cout << "-----IN ADDING CHOICE=0" << std:endl;
                    order.displayOrder();
                    break;
                }

                std::shared_ptr<Item> item = menu.chooseItem(choice);

                if (item)
                {
                    std::cout << "Added " << item->getName() << " to order." << std::endl;
                    std::cout << std::endl;
                    order.addItem(item); //adding the item to the order vector
                    order.displayOrder();
                }
                else
                {
                    std::cout << "Invalid item choice. Please try again." << std::endl;
                }
            }
        }
        //END OF ADD ITEM
        // 
        //-------------------------------------------------------------
        //---------REMOVE ITEM OPTION
        else if (command.compare("remove") == 0)
        {
            bool removeFlag = true;
            if (order.getOrderSize() == 0)
            {
                std::cout << std::endl;
                std::cout << "There are no items in the order to remove." << std::endl;
                std::cout << std::endl;
            }
            else
            {
                std::cout << std::endl;
                std::cout << "Choose item numbers to remove from order (enter item numbers, 0 to finish): " << std::endl;
                int choice;
                while (removeFlag)
                {
                    std::cout << "*********-REMOVE ITEM-*********" << std::endl;
                    std::cout << "Enter item no. or enter 0 to end" << std::endl << ">";
                    std::cin >> choice;

                    if (std::cin.fail())
                    {
                        std::cin.clear(); // Clear the error state
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                        std::cout << "Invalid input. Please enter a number." << std::endl;
                        continue;
                    }

                    if (choice == 0)
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears the input buffer
                        std::cout << std::endl;
                        removeFlag = false;
                        break;
                    }

                    int indexToRemove = choice - 1;
                    if (indexToRemove >= 0 && indexToRemove < order.getOrderSize())
                    {
                        order.removeItem(indexToRemove); //removes the item from the order
                        std::cout << "Removed item " << (indexToRemove + 1) << " from order." << std::endl;

                        //updates the order display after removal
                        order.displayOrder();

                        //checks if order is now empty after removal
                        if (order.getOrderSize() == 0)
                        {
                            std::cout << "No items left in the order." << std::endl;
                            removeFlag = false; //exit removal loop if order is empty (doesn't work, crashes)
                            break;
                        }
                    }
                    else
                    {
                        std::cout << "Invalid item number. Please try again." << std::endl;
                    }
                }
            }
        }

        //END OF REMOVE ITEM
        // 
        //-------------------------------------------------------------
        //--------CHECKOUT OPTION
        else if (command.compare("checkout") == 0) 
        {
            std::cout << std::endl;
            std::cout << "=================================--CHECKOUT--==============================" << std::endl;
            order.displayOrder();
            std::cout << "===========================================================================" << std::endl;
            std::cout << "Total Price: £" << order.getTotalPrice() << std::endl;
            std::cout << std::endl;
            std::cout << "-----------------------------------Completed------------------------------" << std::endl << std::endl;

            //resets the order after checkout
            order.clearOrder();
        }
        else if (command.compare("help") == 0) //help menu of all commands
        {
            std::cout << std::endl;
            std::cout << "Available commands:" << std::endl;
            std::cout << "help - Display the available commands." << std::endl; //help
            std::cout << "menu - Display the menu." << std::endl; //menu
            std::cout << "add <item numbers> - Keep adding items to the order, 0 to end." << std::endl; //add
            std::cout << "remove <item numbers> - Keep removing items from the order, 0 to end." << std::endl; //remove
            std::cout << "checkout - Display the final order (receipt) and total price." << std::endl; //checkout
            std::cout << "exit - Exit the application." << std::endl; //exit
            std::cout << std::endl;
        }

        delete[] cstr;
    }

    std::cout << "Press any key to quit...";
    std::getchar();

    return 0;
}
