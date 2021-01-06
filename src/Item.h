//
// Created by 劉瑄穎 on 2021/1/2.
//

#ifndef ITEM_H
#define ITEM_H
#include"includeSDL.h"
#include"BasicObject.h"

enum ItemList{
	star,
	gun,
	invisible_cloap,
};

class Item :public BasicObject{
private:
    SDL_Point pos_on_map;
    SDL_Point pos_on_screen;
    ItemList type;

public:
    void createitem(ItemList&);
    bool handleEvents(SDL_Event& e);
    void update();
    bool use();
};


#endif //ITEM_H
