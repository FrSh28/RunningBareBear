extern int mode;
#ifndef RUNNER_H
#define RUNNER_H
#include "BasicObject.h"
#include "includeSDL.h"
#include "Character.h"
#include "Game.h"
#include "UserEvent.h"
#include "Map.h"

class Item;
class Map;

enum character_list{BEAR};
enum face {DOWN,LEFT,RIGHT,UP};
class Runner:public Character{
private:
    std::string username;
    face direction;             // character direction(used for render different graphs)
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
    Item* backpack;             // item in hand
    Map* map;
    static Runner* runnerInstance;

    inline void operator++(int);// operator overloading to add strength (meat)

public:
    Runner(SDL_Point&, SDL_Point&,character_list = BEAR);
    Runner(Runner&);
    ~Runner();
    bool handleEvents(SDL_Event &e);
    bool update();
    void move();
    bool checkbackpack();               //check whether the backpack is empty
    bool collisionBox(SDL_Rect&);
    void checkCollision();
    void initclips();
    void setMapPos(SDL_Point&);         // set big grid on map
    void setPixelPos(SDL_Point&);       // set small grid on map (center)
    //void setScreenPos(SDL_Point&);      // set rectOnScreen
    void updateMapPos(SDL_Point&);      // ask map for big grid and update MapPos
    SDL_Point getMapPos() const;        // get big grid on map
    virtual SDL_Point getPixelPos()const;       // get small grid on map (center)
    int getStrength()const;  // get strength
    static const int gridWidth; // the width of grid on map
    static const int gridHeight;// the height of grid on map
    inline static Runner& GetRunner() { return *runnerInstance; }
};


#endif //RUNNER_H
