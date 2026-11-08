#pragma once

#include <vector>

#include "Item.h"

class ItemManager
{
private:
    std::vector<Item> mItems;

public:
    bool Add(const Item& item);
    void Remove(int id);
    const Item* Find(int id) const;
    void SortByValue();
    void PrintAll() const;
};