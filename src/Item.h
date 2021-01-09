//
// Created by 劉瑄穎 on 2021/1/2.
//

#ifndef ITEM_H
#define ITEM_H
#include"includeSDL.h"
#include"BasicObject.h"

enum ItemList{BAD_ITEM, STAR, INVISIBLE_CLOAK, WATER, CHICKEN_LEG, SHEET, LIBRARY, PE_TEACHER,
        TA, JOKE, CHEM_TEACHER, WEBWORK, TOTAL_ITEM };

class Item :public BasicObject
{
protected:
    ItemList type;
public:
    Item(std::string _name = "");
    virtual bool handleEvents(SDL_Event& e)=0;
    virtual bool update()=0;
    ItemList getItemType()const;
};

Item* createItem(ItemList& list);

class Star:public Item
{
public:
    Star();
    ~Star();
    bool handleEvents(SDL_Event& e);
    bool update();
};

class Invisible_Cloak:public Item
{
public:
    Invisible_Cloak();
    ~Invisible_Cloak();
    bool handleEvents(SDL_Event& e);
    bool update();
};

class Water:public Item
{
public:
    Water();
    ~Water();
    bool handleEvents(SDL_Event& e);
    bool update();
};

class Chicken_Leg:public Item
{
public:
    Chicken_Leg();
    ~Chicken_Leg();
    bool handleEvents(SDL_Event& e);
    bool update();
};

class Sheet:public Item
{
public:
    Sheet();
    ~Sheet();
    bool handleEvents(SDL_Event& e);
    bool update();
};

class Library:public Item
{
public:
    Library();
    ~Library();
    bool handleEvents(SDL_Event& e);
    bool update();
};
class PE_Teacher:public Item
{
public:
    PE_Teacher();
    ~PE_Teacher();
    bool handleEvents(SDL_Event& e);
    bool update();
};

class TeacherAssistant:public Item
{
public:
    TeacherAssistant();
    ~TeacherAssistant();
    bool handleEvents(SDL_Event& e);
    bool update();
};

class Joke:public Item
{
public:
    Joke();
    ~Joke();
    bool handleEvents(SDL_Event& e);
    bool update();
};

class CHEM_Teacher:public Item
{
public:
    CHEM_Teacher();
    ~CHEM_Teacher();
    bool handleEvents(SDL_Event& e);
    bool update();
};

class WebWork:public Item
{
public:
    WebWork();
    ~WebWork();
    bool handleEvents(SDL_Event& e);
    bool update();
};

#endif //ITEM_H
