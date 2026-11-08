#include "ItemManager.h"
#include <iostream>
#include <algorithm>


bool ItemManager::Add(const Item& item)
{
    //登録済みの場合は失敗する
    const auto it = std::find_if(mItems.begin(), mItems.end(), [&item](const auto& i)
        {
            return item.mId == i.mId;
        });
    if (it != mItems.end())
    {
        return false;
    }
    mItems.push_back(item);
    return true;
}
void ItemManager::Remove(int id)
{
    auto it = std::remove_if(mItems.begin(), mItems.end(), [id](const auto& i)
        {
            return i.mId == id;
        });
    if (it != mItems.end())
    {
        mItems.erase(it, mItems.end());
    }
}

const Item* ItemManager::Find(int id) const
{
    const auto it = std::find_if(mItems.begin(), mItems.end(), [id](const auto& i)
        {
            return i.mId == id;
        });
    if (it != mItems.end())
    {
        return &(*it);
    }
    return nullptr;
}
void ItemManager::SortByValue()
{
    std::sort(mItems.begin(),
        mItems.end(), [](const Item& a, const Item& b)
        {
            return a.mValue < b.mValue;
        });
}
void ItemManager::PrintAll() const
{
    for (const auto& i : mItems)
    {
        std::cout << "id:" << i.mId << " name " << i.mName << " value " << i.mValue << "\n";
    }
    std::cout << "\n";
}
