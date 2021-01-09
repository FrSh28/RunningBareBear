//
// Created by 劉瑄穎 on 2021/1/2.
//
#include "Item.h"
Item* createItem(ItemList& list)
{
    //a random Item
    switch (list)
    {
        case STAR:
            return  new Star;
        //case INVISIBLE_CLOAK:
        //    return new Invisible_Cloak;
        case POTION:
            return new Potion;
        case MEAT:
            return new Meat;
        case SHEET:
            return new Sheet;
        case LIBRARY:
            return new Library;
        case PE_TEACHER:
            return new PE_Teacher;
        case TA:
            return new TeacherAssistant;
        //case JOKE:
        //    return new Joke;
        //case CHEM_TEACHER:
        //    return new CHEM_Teacher;
        case WEBWORK:
            return new WebWork;
    }
}
Item::Item(std::string _name):BasicObject(_name)
{}
ItemList Item::getItemType() const {return type;}

//Star
Star::Star():Item("Star")
{}
Star::~Star(){}
bool Star::handleEvents(SDL_Event& e)
{}
bool Star::update()
{}

//Invisible Cloak
/*Invisible_Cloak::Invisible_Cloak():Item("Invisible Cloak"){}
Invisible_Cloak::~Invisible_Cloak(){}
bool Invisible_Cloak::handleEvents(SDL_Event &e) {}
bool Invisible_Cloak::update() {}
*/

//Potion
Potion::Potion():Item("Potion") {}
Potion::~Potion(){}
bool Potion::handleEvents(SDL_Event &e)
{
    if(e.type == ITEM_USED)
    {
        if(e.user.code == POTION)
        {
            //+++strength
        }
    }
}
bool Potion::update() {}

//Meat
Meat::Meat():Item("Meat") {}
Meat::~Meat(){}
bool Meat::handleEvents(SDL_Event &e) {}
bool Meat::update() {}

//Sheet
Sheet::Sheet():Item("Sheet") {}
Sheet::~Sheet(){}
bool Sheet::handleEvents(SDL_Event &e) {}
bool Sheet::update() {}

//Library
Library::Library():Item("Library") {}
Library::~Library(){}
bool Library::handleEvents(SDL_Event &e) {}
bool Library::update() {}

//Physical education Teacher
PE_Teacher::PE_Teacher():Item("Physical Education Teacher") {}
PE_Teacher::~PE_Teacher(){}
bool PE_Teacher::handleEvents(SDL_Event &e) {}
bool PE_Teacher::update() {}

//TA
TeacherAssistant::TeacherAssistant():Item("Teacher Assistant"){}
TeacherAssistant::~TeacherAssistant(){}
bool TeacherAssistant::handleEvents(SDL_Event &e) {}
bool TeacherAssistant::update() {}

/*
//Joke
Joke::Joke() {}
Joke::~Joke(){}
bool Joke::handleEvents(SDL_Event &e) {}
bool Joke::update() {}

//Chemistry Teacher
CHEM_Teacher::CHEM_Teacher():Item("Chemistry Teacher") {}
CHEM_Teacher::~CHEM_Teacher(){}
bool CHEM_Teacher::handleEvents(SDL_Event &e) {}
bool CHEM_Teacher::update() {}
*/

//WebWork
WebWork::WebWork():Item("WebWork"){}
WebWork::~WebWork(){}
bool WebWork::handleEvents(SDL_Event &e) {}
bool WebWork::update() {}