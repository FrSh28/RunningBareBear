extern int mode;
#ifndef RUNNER_H
#define RUNNER_H
#include"BasicObject.h"
#include"includeSDL.h"
#include"Wall.h"
#include"Map.h"
#include"Game.h"

enum character_list{professor_hsieh,bear,soldier};
class Runner:public BasicObject{
private:
    std::string username;
    SDL_Point PixelPos;         // small grid on map
    SDL_Point MapPos;           // big grid on map
    int Rvelocity_x;            // runner x velocity
    int Rvelocity_y;            // runner y velocity
    int Rvelocity;              // the velocity when pressing button
    double Rstrength;           // the strength of runner
    int sprint_velocity;        // the velocity added when sprinting
    Map* map;
    Game &game = Game::GetGame();

public:
    Runner(character_list);
    ~Runner();
    bool handleEvents(SDL_Event &e);
    void update();
    void move();
    bool collision(Wall*);
    Wall* getwall()const;
    void initclips();
    void setMapPos(SDL_Point&);         // set big grid on map
    void setPixelPos(SDL_Point);        // set small grid on map (center)
    SDL_Point getMapPos() const;       // get big grid on map
    SDL_Point getPixelPos()const;      // get small grid on map (center)
};


#endif //RUNNER_H
