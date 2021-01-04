//
// Created by 劉瑄穎 on 2021/1/2.
//

#ifndef ITEM_H
#define ITEM_H
#include"includeSDL.h"
#include"Renderable.h"


enum itemlist{star,gun,invisible_cloap};
class Item :public Renderable{
private:
    SDL_Point pos_on_map;
    SDL_Point pos_on_screen;

public:
    void createitem(itemlist&);
    bool handleEvents(SDL_Event& e);
    void update();
    bool use();
};


#endif //ITEM_H
