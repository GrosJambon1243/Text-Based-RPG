#pragma once
#include <stack>
#include <vector>

#include "ShopItem.h"

using namespace std;
class Hall
{
public:
    int totalGold;
    vector<ShopItem> hallItem;
    vector<string> trophies;
    Hall(const vector<ShopItem>& hall_item)
        : hallItem(hall_item)
    {
        totalGold = 0;
    }

    
private:
protected:
    
};
