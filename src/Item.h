//
// Created by 劉瑄穎 on 2021/1/2.
//

#ifndef ITEM_H
#define ITEM_H
#include"includeSDL.h"
#include"BasicObject.h"

enum ItemList{BAD_ITEM,STAR,GUN,INVISIBLE_CLOAK,WATER,CHICKEN_LEG,TOTAL_ITEM};

class Item :public BasicObject{
private:
    SDL_Point pos_on_map;
    SDL_Point pos_on_screen;
    ItemList type;

public:
    bool handleEvents(SDL_Event& e);
    void update();
    ItemList getItemType()const;
};

Item* createItem(ItemList& list);

class Star:public Item
{

public:
    Star();


};

class Gun:public Item
{
public:
    Gun();
};

class Invisible_Cloak:public Item
{
public:
    Invisible_Cloak();
};
class Water:public Item
{
public:
    Water();
};
class Chicken_Leg:public Item
{
public:
    Chicken_Leg();
};




#endif //ITEM_H
