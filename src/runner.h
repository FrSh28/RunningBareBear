//
// Created by 劉瑄穎 on 2020/12/31.
//
extern int mode;
#ifndef SRC_RUNNER_H
#define SRC_RUNNER_H
#include"Renderable.h"
#include<string>

enum character_list{professor_hsieh,bear};
class runner:public Renderable{
private:
    SDL_Point current_pos;
    int speed;
public:
    runner(char * ,int );
    ~runner();
    void handleEvents(SDL_Event &e);
    void update();

};


#endif //SRC_RUNNER_H
