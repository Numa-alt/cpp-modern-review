#include <iostream>

#include "ItemManager.h"

int main()
{
    ItemManager itemManager;

    std::cout << "cpp-modern-review\n";

    Item itemA{ 0,"A",100 };
    Item itemB{ 1,"B",80 };
    Item itemC{ 2,"C",150 };
    Item itemD{ 3,"D",90 };

    itemManager.Add(itemA);
    itemManager.Add(itemB);
    itemManager.Add(itemC);
    itemManager.Add(itemD);

    itemManager.PrintAll();

    itemManager.SortByValue();

    itemManager.PrintAll();

    auto item = itemManager.Find(4);
    if (!item)
    {
        std::cout << "NotFind id 4 \n";
    }
    auto item2 = itemManager.Find(0);
    if (item2)
    {
        std::cout << "Find id 0 \n";
    }

    itemManager.Remove(4);

    itemManager.PrintAll();

    itemManager.Remove(2);

    itemManager.PrintAll();

    return 0;
}