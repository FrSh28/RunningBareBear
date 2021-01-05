//
// Created by 劉瑄穎 on 2020/12/31.
//
#include "Runner.h"
#include<cstdlib>
character_list character;
Runner::Runner(character_list character ):
Renderable("Runner"),Rstrength(100)
{
    pos_on_screen.x = 640;
    pos_on_screen.y = 360;
    srand(time(0));
    //pos_on_map.x = rand() % Mapwidth;
    srand(time(0));
    //pos_on_map.y =rand() % Mapheight;
    while(pos_on_map is wall)
    {
        srand(time(0));
        //pos_on_map.x = rand() % Mapwidth;
        srand(time(0));
        //pos_on_map.y =rand() % Mapheight;
    }

    if (mode==1)
    {
        //texture = loadMedia(TEXTURE_XXX);
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
    rec_on_map.x = pos_on_map.x;
    rec_on_map.y = pos_on_map.y;
    rec_on_map.w = 40;
    rec_on_map.h = 32;
}

Runner::~Runner()
{
    //show win or lose

}


int Runner::R_get_Xpos_on_map() const{return pos_on_map.x;}
int Runner::R_get_Ypos_on_map() const {return pos_on_map.y;}

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
    move();
    //posOnWindow = Map::convertPos(pos);
    rec_on_map.x = pos_on_map.x;
    rec_on_map.y = pos_on_map.y+50;

}

bool Runner::collision(Wall* wall)
{
    bool collision = true;
    if(wall !=NULL)
    {
        if (rec_on_map.x>=wall.rec_on_map.x+wall.rec_on_map.w){return false;}
        if(rec_on_map.x+w=<wall.rec_on_map.x){return false;}
        if(rec_on_map.y=<wall.rec_on_map.y+wall.rec_on_map.h){return false;}
        if(rec_on_map.y+rec_on_map.h>=wall.rec_on_map.y){return false;}
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
        if(pos_on_map.x+1 is wall)
        {
            //wall = the wall below;
            return wall;
        }
    }
    return wall;
}
