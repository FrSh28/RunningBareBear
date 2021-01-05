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
    int sprint_velocity;
    std::string name;

public:
    Runner(character_list  );
    ~Runner();
    bool handleEvents(SDL_Event &e);
    void update();
    int R_get_Xpos_on_map()const;
    int R_get_Ypos_on_map()const;
    void move(Wall&);
    void collision(Wall&);


    //change character?
    // runner* operator=(runner&);


};


#endif //RUNNER_H
