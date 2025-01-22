#pragma once
#include <iostream>
#include <string>

class ShopItem
{
public:
    std::string description;
    std::string name;
    int price;

    ShopItem(const std::string& description, const std::string& name, int price)
        : description(description),
          name(name),
          price(price)
    {
    }

    void DisplayItemInfo()
    {
        std::cout << name << " || " << std::to_string(price) << " Gold" <<"\n - " << description;
    }

    void DisplayItemHall()
    {
        std::cout << name << "\n - " << description << "\n";
    }

    //~ShopItem();
};
