//
// Created by 劉瑄穎 on 2021/1/2.
//

#ifndef ITEM_H
#define ITEM_H
#include"includeSDL.h"
#include"BasicObject.h"

enum ItemList{Star,Gun,Invisible_Cloak,Water,Chicken_Leg,Total_Item};

class Item :public BasicObject{
private:
    SDL_Point pos_on_map;
    SDL_Point pos_on_screen;

public:
    bool handleEvents(SDL_Event& e);
    void update();
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
