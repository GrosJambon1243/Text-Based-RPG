#pragma once
#include <stack>

#include "ShopItem.h"

class Shop
{
public:
     Shop(const std::stack<ShopItem>& shop_item)
        : shopItem(shop_item)
    {
    }
    std::stack<ShopItem> shopItem;

    void DisplayTopItem()
    {
        shopItem.top().DisplayItemInfo();
    }
    
};
