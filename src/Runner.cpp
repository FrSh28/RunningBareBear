//
// Created by 劉瑄穎 on 2020/12/31.
//
#include "Runner.h"
character_list character;

const int ANIMATION_FRAMES = 3;
const int TOTAL_FRAMES = 12;
SDL_Rect Clip [TOTAL_FRAMES];

const int Runner::gridWidth = Map::getPixelWidth();
const int Runner::gridHeight = Map::getPixelHeight();
Runner::Runner(SDL_Point& InitialMapPos,SDL_Point& InitialPixelPos, character_list character):
BasicObject("Runner"), strength(100), map(&Map::getMap()), width(40),
height(32), updateRate(6), direction(DOWN) {
    initclips();
    if (mode == 1) {
        //texture = loadMedia(TEXTURE_XXX);     // ref Files.h --by FrSh
        /*posOnWindow->x = (int);
        posOnTexture->x = (int);
        posOnWindow->y = (int);
        posOnTexture->y = (int);
        posOnWindow->w = (int);
        posOnTexture->w = (int);
        posOnWindow->h = (int);
        posOnTexture->h = (int);*/

        rectOnTexture = Clip[0];

        switch (character) {
            case BEAR:
                velocity = 00000;
                sprint_velocity = 00000;
                username = "bear";
                break;
        }
    }
    //set Initial PixelPos
    setPixelPos(InitialPixelPos);
    //set Initial MapPos
    setMapPos(InitialMapPos);

}
void Runner::setMapPos(SDL_Point &Set)
{
    MapPos.x = Set.x;
    MapPos.y = Set.y;
}
void Runner::setPixelPos(SDL_Point &Set)
{
    PixelPos.x = Set.x;
    PixelPos.y = Set.y;
    // change PixelPos to top left
    PixelPos.x -=  width/2 ;
    PixelPos.y -=  height/2;
}
Runner::~Runner(){/*show win or lose*/}
SDL_Point Runner::getMapPos()const{return MapPos;}       // get big grid on map
SDL_Point Runner::getPixelPos()const                     // get small grid on map (center)
{
    SDL_Point center;
    center.x = PixelPos.x + width/2;
    center.y = PixelPos.y + height/2;
    return center;
}

void Runner::updateMapPos(SDL_Point& currentMappos)       // ask map for big grid and update MapPos
{currentMappos = map->getRunnerMapPos();}

bool Runner::handleEvents(SDL_Event &e)
{
    bool success=false;
    if(mode==1)
    {
        //if a key is pressed
        if(e.type==SDL_KEYDOWN && e.key.repeat == 0 )
        {
            //adjust velocity
            switch(e.key.keysym.sym)
            {
                case SDLK_SPACE:
                    velocity += sprint_velocity;
                    updateRate = 3;
                    return true;
                case SDLK_s:
                    velocity_y += velocity;
                    direction = DOWN;
                    return  true;
                case SDLK_w:
                    velocity -= velocity;
                    direction = UP;
                    return true;
                case SDLK_d:
                    velocity_x += velocity;
                    direction = RIGHT;
                    return true;
                case SDLK_a:
                    velocity_x -= velocity;
                    direction = LEFT;
                    return true;
                case SDLK_e:
                    //pickup throw switch
                    Item* tmp;
                    tmp = map->pickItem(MapPos);
                    map->placeItem(MapPos,backpack);
                    backpack = tmp;
                    return true;
                case SDLK_q:
                    createUserEvent(ITEM_USED,backpack->getItemType(),NULL,NULL);
                    return true;
            }
        }
        //if a key is released
        else if(e.type==SDL_KEYUP && e.key.repeat == 0)
        {
            //Adjust the velocity
            switch( e.key.keysym.sym )
            {
                case SDLK_SPACE:
                    velocity -= sprint_velocity;
                    updateRate = 6;
                    return true;
                case SDLK_w:
                    velocity_y -= velocity;
                    return true;
                case SDLK_s:
                    velocity_y += velocity;
                    return true;
                case SDLK_a:
                    velocity_x -= velocity;
                    return true;
                case SDLK_d:
                    velocity_x += velocity;
                    return true;
            }
        }
    }
    return success;
}

void Runner::move()
{
    //right and left
    PixelPos.x += velocity_x;
    //up and down
    PixelPos.y += velocity_y;
    checkCollision();
}

bool Runner::checkbackpack()    // if backpack is empty return true
{
    if(backpack == NULL){return true;}
    else{return false;}
}

bool Runner::update()
{
    static int frame = 0;
    // move(update PixelPos)
    move();
    // deal strength
    if(velocity_x!=0||velocity_y!=0)
    {
        strength -= 0.05;
        if(abs(velocity_x) == sprint_velocity+velocity || abs(velocity_y) == sprint_velocity+velocity)
        {strength -= 0.05;}
    }

    // use map function to calculate MapPos and update
    MapPos = map->mapPosTopixelPos(SDL_Point({PixelPos.x+width/2,PixelPos.y+height/2}));

    //Render current frame
    rectOnTexture = Clip[direction*3+frame/updateRate];
    //render??;

    // go to next frame
    frame ++;
    // cycle animation
    if(frame/updateRate == ANIMATION_FRAMES){frame=0;}

    return true;
}

bool Runner::collisionBox(SDL_Rect& square)
{
    bool collision = true;
    if(PixelPos.x        > square.x+square.w){return false;}
    if(PixelPos.x+width  < square.x){return false;}
    if(PixelPos.y        < square.y+square.h){return false;}
    if(PixelPos.y+height > square.y){return false;}
    return collision;
}

void Runner::checkCollision()
{
    // right
    if(velocity_x>0)
    {
        // check right top
        if(map->isWall(SDL_Point({MapPos.x+1,MapPos.y-1})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x+1,MapPos.y-1})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x+1,MapPos.y-1})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
        // chek right middle
        if(map->isWall(SDL_Point({MapPos.x+1,MapPos.y})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x+1,MapPos.y})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x+1,MapPos.y})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
        // check right bottom
        if(map->isWall(SDL_Point({MapPos.x+1,MapPos.y+1})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x+1,MapPos.y+1})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x+1,MapPos.y+1})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
    }

    // left
    if(velocity_x<0)
    {
        // check left top
        if(map->isWall(SDL_Point({MapPos.x-1,MapPos.y-1})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x-1,MapPos.y-1})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x-1,MapPos.y-1})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
        // chek left middle
        if(map->isWall(SDL_Point({MapPos.x+1,MapPos.y})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x-1,MapPos.y})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x-1,MapPos.y})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
        // check right bottom
        if(map->isWall(SDL_Point({MapPos.x+1,MapPos.y+1})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x-1,MapPos.y+1})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x-1,MapPos.y+1})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.x -= velocity_x;
            }
        }
    }

    // up
    if(velocity_y<0)
    {
        // check top left
        if(map->isWall(SDL_Point({MapPos.x-1,MapPos.y-1})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x-1,MapPos.y-1})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x-1,MapPos.y-1})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
        // chek top middle
        if(map->isWall(SDL_Point({MapPos.x,MapPos.y-1})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x,MapPos.y-1})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x,MapPos.y-1})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
        // check top right
        if(map->isWall(SDL_Point({MapPos.x+1,MapPos.y-1})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x+1,MapPos.y-1})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x+1,MapPos.y-1})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
    }

    // down
    if(velocity_y>0)
    {
        // check below left
        if(map->isWall(SDL_Point({MapPos.x-1,MapPos.y+1})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x-1,MapPos.y+1})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x-1,MapPos.y+1})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
        // chek below middle
        if(map->isWall(SDL_Point({MapPos.x,MapPos.y+1})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x,MapPos.y+1})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x,MapPos.y+1})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
        // check below right
        if(map->isWall(SDL_Point({MapPos.x+1,MapPos.y+1})))
        {
            SDL_Point wallPos;
            wallPos.x = map->pixelPosTomapPos(SDL_Point({MapPos.x+1,MapPos.y+1})).x;
            wallPos.y = map->pixelPosTomapPos(SDL_Point({MapPos.x+1,MapPos.y+1})).y;
            SDL_Rect wall({wallPos.x,wallPos.y,gridWidth,gridHeight});
            if(collisionBox(wall))
            {
                PixelPos.y -= velocity_y;
            }
        }
    }
}

void Runner::initclips()                // init render clips
{
    // Down
    Clip[0].x = 0000;
    Clip[0].y = 0000;
    Clip[0].w = 0000;
    Clip[0].h = 0000;

    Clip[1].x = 0000;
    Clip[1].y = 0000;
    Clip[1].w = 0000;
    Clip[1].h = 0000;

    Clip[2].x = 0000;
    Clip[2].y = 0000;
    Clip[2].w = 0000;
    Clip[2].h = 0000;

    //Right
    Clip[3].x = 0000;
    Clip[3].y = 0000;
    Clip[3].w = 0000;
    Clip[3].h = 0000;

    Clip[4].x = 0000;
    Clip[4].y = 0000;
    Clip[4].w = 0000;
    Clip[4].h = 0000;

    Clip[5].x = 0000;
    Clip[5].y = 0000;
    Clip[5].w = 0000;
    Clip[5].h = 0000;

    //Left
    Clip[6].x = 0000;
    Clip[6].y = 0000;
    Clip[6].w = 0000;
    Clip[6].h = 0000;

    Clip[7].x = 0000;
    Clip[7].y = 0000;
    Clip[7].w = 0000;
    Clip[7].h = 0000;

    Clip[8].x = 0000;
    Clip[8].y = 0000;
    Clip[8].w = 0000;
    Clip[8].h = 0000;

    //Up
    Clip[9].x = 0000;
    Clip[9].y = 0000;
    Clip[9].w = 0000;
    Clip[9].h = 0000;

    Clip[10].x = 0000;
    Clip[10].y = 0000;
    Clip[10].w = 0000;
    Clip[10].h = 0000;

    Clip[11].x = 0000;
    Clip[11].y = 0000;
    Clip[11].w = 0000;
    Clip[11].h = 0000;
}