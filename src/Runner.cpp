//
// Created by 劉瑄穎 on 2020/12/31.
//
#include "Runner.h"
character_list character;

const int WALKING_ANIMATION_FRAMES = 12;
SDL_Rect Current_Clip [WALKING_ANIMATION_FRAMES];

Runner::Runner(character_list character ):
BasicObject("Runner"),Rstrength(100),map(&Map::getMap())
{
    initclips();
    if (mode==1)
    {
        //texture = loadMedia(TEXTURE_XXX);     // ref Files.h --by FrSh
        /*posOnWindow->x = (int);
        posOnTexture->x = (int);
        posOnWindow->y = (int);
        posOnTexture->y = (int);
        posOnWindow->w = (int);
        posOnTexture->w = (int);
        posOnWindow->h = (int);
        posOnTexture->h = (int);*/

        switch(character)
        {
            case professor_hsieh:
                Rvelocity = 00000;
                sprint_velocity = 00000;
                username="professor";
                break;

            case bear:
                Rvelocity = 00000;
                sprint_velocity = 00000;
                username = "bear";
                break;

            case soldier:
                Rvelocity = 00000;
                sprint_velocity = 00000;
                username = "soldier";
                break;
        }
    }
    // set big grid on map
    setMapPos(MapPos);
    // set small grid on map (center)
    setPixelPos(PixelPos);
    // change PixelPos to top left
    PixelPos.x -= runner width/2 ;
    PixelPos.y -= runner height/2;
    // set rect for collision
    rec_on_map.x = pos_on_map.x;
    rec_on_map.y = pos_on_map.y;
    rec_on_map.w = 40;
    rec_on_map.h = 32;
}

Runner::~Runner(){/*show win or lose*/}
SDL_Point Runner::getMapPos()const{return MapPos;}       // get big grid on map
SDL_Point Runner::getPixelPos()const                     // get small grid on map (center)
{
    SDL_Point center;
    center.x = PixelPos.x + character width/2;
    center.y = PixelPos.y + character height/2;
    return center;
}

void Runner::updategrid(SDL_Point& currentpoint)
{
    SDL_Point tmp;
    tmp.x = currentpoint.x + rec_on_map.w/2;
    tmp.y = currentpoint.y + rec_on_map.h/2;
    grid = Map::pixelposition
}

bool Runner::handleEvents(SDL_Event &e)
{
    bool success=true;
    if(mode==1)
    {
        //if a key is pressed
        if(e.type==SDL_KEYDOWN && e.key.repeat == 0 )
        {
            //adjust velocity
            switch(e.key.keysym.sym)
            {
                case SDLK_SPACE: Rvelocity += sprint_velocity;
                case SDLK_s: Rvelocity_y += Rvelocity; break;
                case SDLK_w: Rvelocity -= Rvelocity; break;
                case SDLK_d: Rvelocity_x += Rvelocity; break;
                case SDLK_a: Rvelocity_x -= Rvelocity; break;
                case SDLK_e: pickup = true;
            }
        }
        //if a key is released
        else if(e.type==SDL_KEYUP && e.key.repeat == 0)
        {
            //Adjust the velocity
            switch( e.key.keysym.sym )
            {
                case SDLK_SPACE: Rvelocity -= sprint_velocity;
                case SDLK_UP: Rvelocity_y -= Rvelocity; break;
                case SDLK_DOWN: Rvelocity += Rvelocity; break;
                case SDLK_LEFT: Rvelocity_x -= Rvelocity; break;
                case SDLK_RIGHT: Rvelocity_x += Rvelocity; break;
                case SDLK_e: pickup = false;
            }
        }

    }
    return success;
}

void Runner::move()
{
    //right and left
    pos_on_map.x += Rvelocity_x;
    //up and down
    pos_on_map.y += Rvelocity_y;

    if(collision(getwall()))
    {
        //right and left
        pos_on_map.x -= Rvelocity_x;
        //up and down
        pos_on_map.y -= Rvelocity_y;
    }
}

void Runner::update()
{
    static int frame = 0;

    move();
    if(Rvelocity_x!=0||Rvelocity_y!=0)
    {
        Rstrength -= 0.05;
        if(Rvelocity_x == abs(sprint_velocity+Rvelocity)||Rvelocity_y == abs(sprint_velocity+Rvelocity))
        {Rstrength -= 0.05;}
    }
    //posOnWindow = Map::convertPos(pos);
    rec_on_map.x = pos_on_map.x;
    rec_on_map.y = pos_on_map.y;
    frame ++;
    updategrid(pos_on_map);


    if(frame>1200){frame=0;}

}

bool Runner::collision(Wall* wall)
{
    bool collision = true;
    if(wall !=NULL)
    {
        if (rec_on_map.x > wall.rec_on_map.x+wall.rec_on_map.w){return false;}
        if(rec_on_map.x+rec_on_map.w < wall.rec_on_map.x){return false;}
        if(rec_on_map.y < wall.rec_on_map.y+wall.rec_on_map.h){return false;}
        if(rec_on_map.y+rec_on_map.h > wall.rec_on_map.y){return false;}
    }
    return collision;

}

Wall* Runner::getwall()
{
    Wall* wall=NULL;
    //check right grid
    if(Rvelocity_x>0)
    {
        if(pos_on_map.x+1 is wall)
        {
            //wall = the wall right;
            return wall;
        }
    }

    //check left grid
    if(Rvelocity_x<0)
    {
        if(pos_on_map.x-1 is wall)
        {
            //wall = the wall left;
            return wall;
        }
    }

    //check up grid
    if(Rvelocity_y<0)
    {
        if(pos_on_map.y-1 is wall)
        {
            //wall = the wall above;
            return wall;
        }
    }

    //check below grid
    if(Rvelocity_y>0)
    {
        if(pos_on_map.y+1 is wall)
        {
            //wall = the wall below;
            return wall;
        }
    }
    return wall;
}

void Runner::initclips()                // init render clips
{
    Current_Clip[0].x = 0000;
    Current_Clip[0].y = 0000;
    Current_Clip[0].w = 0000;
    Current_Clip[0].h = 0000;

    Current_Clip[1].x = 0000;
    Current_Clip[1].y = 0000;
    Current_Clip[1].w = 0000;
    Current_Clip[1].h = 0000;

    Current_Clip[2].x = 0000;
    Current_Clip[2].y = 0000;
    Current_Clip[2].w = 0000;
    Current_Clip[2].h = 0000;

    Current_Clip[3].x = 0000;
    Current_Clip[3].y = 0000;
    Current_Clip[3].w = 0000;
    Current_Clip[3].h = 0000;

    Current_Clip[4].x = 0000;
    Current_Clip[4].y = 0000;
    Current_Clip[4].w = 0000;
    Current_Clip[4].h = 0000;

    Current_Clip[5].x = 0000;
    Current_Clip[5].y = 0000;
    Current_Clip[5].w = 0000;
    Current_Clip[5].h = 0000;

    Current_Clip[6].x = 0000;
    Current_Clip[6].y = 0000;
    Current_Clip[6].w = 0000;
    Current_Clip[6].h = 0000;

    Current_Clip[7].x = 0000;
    Current_Clip[7].y = 0000;
    Current_Clip[7].w = 0000;
    Current_Clip[7].h = 0000;

    Current_Clip[8].x = 0000;
    Current_Clip[8].y = 0000;
    Current_Clip[8].w = 0000;
    Current_Clip[8].h = 0000;

    Current_Clip[9].x = 0000;
    Current_Clip[9].y = 0000;
    Current_Clip[9].w = 0000;
    Current_Clip[9].h = 0000;

    Current_Clip[10].x = 0000;
    Current_Clip[10].y = 0000;
    Current_Clip[10].w = 0000;
    Current_Clip[10].h = 0000;

    Current_Clip[11].x = 0000;
    Current_Clip[11].y = 0000;
    Current_Clip[11].w = 0000;
    Current_Clip[11].h = 0000;
}