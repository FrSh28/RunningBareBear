//
// Created by 劉瑄穎 on 2020/12/31.
//
#include "Runner.h"

bool checkcollision(Runner& player)
{

}

Wall* getwall()
character_list character;
Runner::Runner(character_list character )
{
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
                name="professor";
                break;

            case bear:
                Rvelocity = 00000;
                sprint_velocity = 00000;
                name = "bear";
                break;

            case soldier:
                Rvelocity = 00000;
                sprint_velocity = 00000;
                name = "soldier";
                break;
        }
    }
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
        if(e.type==SDL_KEYDOWN && e.key.repeat == 0 )
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_q: Rvelocity += sprint_velocity;
                case SDLK_UP: Rvelocity_y += Rvelocity; break;
                case SDLK_DOWN: Rvelocity -= Rvelocity; break;
                case SDLK_LEFT: Rvelocity_x += Rvelocity; break;
                case SDLK_RIGHT: Rvelocity_x -= Rvelocity; break;

            }
        }
    }
    return success;
}

void Runner::move(Wall& wall)
{

    //dealing collision


}

void Runner::update()
{
    //posOnWindow = Map::convertPos(pos);
}
