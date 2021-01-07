extern int mode;
#ifndef RUNNER_H
#define RUNNER_H
#include"BasicObject.h"
#include"includeSDL.h"
#include"Wall.h"
#include"Map.h"
#include"Game.h"

enum character_list{professor_hsieh,bear,soldier};
enum face {Down,Left,Right,Up};
class Runner:public BasicObject{
private:
    std::string username;
    face direction;             // character direction(used for render different graphs)
    SDL_Rect* CurrentClip;      // use for render
    SDL_Point PixelPos;         // small grid on map
    SDL_Point MapPos;           // big grid on map
    int velocity_x;             // runner x velocity
    int velocity_y;             // runner y velocity
    int velocity;               // the velocity when pressing button
    double strength;            // the strength of runner
    int sprint_velocity;        // the velocity added when sprinting
    int width;                  // rectangle width (for collision box)
    int height;                 // rectangle height (for collision box)
    int updateRate;             // different update rate according to running or walking
    Map* map;
    Game &game;

public:
    Runner(SDL_Point&, SDL_Point&,character_list=bear);
    ~Runner();
    bool handleEvents(SDL_Event &e);
    void update();
    void move();
    bool collisionBox(SDL_Rect&);
    void checkCollision();
    void initclips();
    void setMapPos(SDL_Point&);         // set big grid on map
    void setPixelPos(SDL_Point&);       // set small grid on map (center)
    void updateMapPos(SDL_Point&);      // ask map for big grid and update MapPos
    SDL_Point getMapPos() const;        // get big grid on map
    SDL_Point getPixelPos()const;       // get small grid on map (center)

    static const int gridWidth; // the width of grid on map
    static const int gridHeight;// the height of grid on map
};


#endif //RUNNER_H
