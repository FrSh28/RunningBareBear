//
// Created by 劉瑄穎 on 2021/1/2.
//

#ifndef WALL_H
#define WALL_H
#include"BasicObject.h"


class Wall :public BasicObject
{
private:
    SDL_Rect rec_on_map;
    SDL_Point pos_on_map;
    SDL_Point pos_on_screen;
public:
    Wall();
    ~Wall();

};


#endif //WALL_H
