//
// Created by 劉瑄穎 on 2021/1/2.
//
#include "Item.h"
Item* createItem(ItemList& list)
{
    //a random item
    switch (list)
    {
        case STAR:
            return  new Star;
        case GUN:
            ;
        case INVISIBLE_CLOAK:
            ;
        case WATER:
            ;
        case CHICKEN_LEG:
            ;

    }
}

ItemList Item::getItemType() const {return type;}
