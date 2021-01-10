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
        case TA1:
            return new TeacherAssistant1;
        case TA2:
            return new TeacherAssistant2;
        case TA3:
            return new TeacherAssistant3;
        //case JOKE:
        //    return new Joke;
        //case CHEM_TEACHER:
        //    return new CHEM_Teacher;
        case WEBWORK1:
            return new WebWork1;
        case WEBWORK2:
            return new WebWork2;
        case WEBWORK3:
            return new WebWork3;
    }
}
Item::Item(std::string _name):BasicObject(_name){}
void Item::setPixelPos(SDL_Point& pixelPos)   // center
{
    rectOnScreen.x = pixelPos.x - rectOnScreen.w / 2;
    rectOnScreen.y = pixelPos.y - rectOnScreen.h / 2;
}
ItemList Item::getItemType() const {return type;}

//Star
Star::Star():Item("Star"){loadImage(STAR);}
Star::~Star(){}
bool Star::handleEvents(SDL_Event& e){return false;}
bool Star::update(){return false;}

//Invisible Cloak
/*Invisible_Cloak::Invisible_Cloak():Item("Invisible Cloak"){}
Invisible_Cloak::~Invisible_Cloak(){}
bool Invisible_Cloak::handleEvents(SDL_Event &e) {}
bool Invisible_Cloak::update() {}
*/

//Potion
Potion::Potion():Item("Potion") {loadImage(POTION_IMAGE);}
Potion::~Potion(){}
bool Potion::handleEvents(SDL_Event &e){return false;}
bool Potion::update() {return false;}

//Meat
Meat::Meat():Item("Meat") {loadImage(MEAT_IMAGE);}
Meat::~Meat(){}
bool Meat::handleEvents(SDL_Event &e) {return false;}
bool Meat::update() {return false;}

//Sheet
Sheet::Sheet():Item("Sheet") {loadImage(SHEET_IMAGE);}
Sheet::~Sheet(){}
bool Sheet::handleEvents(SDL_Event &e) {return false;}
bool Sheet::update() {return false;}

//Library
Library::Library():Item("Library") {loadImage(LIBRARY_IMAGE);}
Library::~Library(){}
bool Library::handleEvents(SDL_Event &e) {return false;}
bool Library::update() {return false;}

//Physical education Teacher
PE_Teacher::PE_Teacher():Item("Physical Education Teacher") {loadImage(PE_Teacher_IMAGE);}
PE_Teacher::~PE_Teacher(){}
bool PE_Teacher::handleEvents(SDL_Event &e) {return false;}
bool PE_Teacher::update() {return false;}

//TA1
TeacherAssistant1::TeacherAssistant1():Item("Teacher Assistant"){loadImage(TA1_IMAGE);}
TeacherAssistant1::~TeacherAssistant1(){}
bool TeacherAssistant1::handleEvents(SDL_Event &e) {return false;}
bool TeacherAssistant1::update() {return false;}

//TA2
TeacherAssistant2::TeacherAssistant2():Item("Teacher Assistant"){loadImage(TA2_IMAGE);}
TeacherAssistant2::~TeacherAssistant2(){}
bool TeacherAssistant2::handleEvents(SDL_Event &e) {return false;}
bool TeacherAssistant2::update() {return false;}

//TA3
TeacherAssistant3::TeacherAssistant3():Item("Teacher Assistant"){loadImage(TA3_IMAGE);}
TeacherAssistant3::~TeacherAssistant3(){}
bool TeacherAssistant3::handleEvents(SDL_Event &e) {return false;}
bool TeacherAssistant3::update() {return false;}

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
WebWork1::WebWork1():Item("WebWork"){}
WebWork1::~WebWork1(){}
bool WebWork1::handleEvents(SDL_Event &e) {return false;}
bool WebWork1::update() {return false;}

WebWork2::WebWork2():Item("WebWork"){}
WebWork2::~WebWork2(){}
bool WebWork2::handleEvents(SDL_Event &e) {return false;}
bool WebWork2::update() {return false;}

WebWork3::WebWork3():Item("WebWork"){}
WebWork3::~WebWork3(){}
bool WebWork3::handleEvents(SDL_Event &e) {return false;}
bool WebWork3::update() {return false;}