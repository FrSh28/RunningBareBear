//
// Created by 劉瑄穎 on 2020/12/31.
//
extern int mode;
#ifndef RUNNER_H
#define RUNNER_H
#include"Renderable.h"
#include"includeSDL.h"
#include"Wall.h"

enum character_list{professor_hsieh,bear,soldier};
class Runner:public Renderable{
private:
    SDL_Point pos_on_screen;
    SDL_Point pos_on_map;
    int Rvelocity_x;
    int Rvelocity_y;
    int Rvelocity;
    int Rstrength;
    std::string name;

public:
    Runner(character_list  );
    ~Runner();
    bool handleEvents(SDL_Event &e);
    void update();
    int get_Xposition_on_map()const;
    int get_Yposition_on_map()const;
    void move(Wall&);


    //change character?
    // runner* operator=(runner&);


};


#endif //RUNNER_H
