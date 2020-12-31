//
// Created by 劉瑄穎 on 2020/12/31.
//

#include "runner.h"
runner::runner(char * ,int )
{
    if (mode==1)
    {
        //texture = loadMedia(TEXTURE_XXX);
        /*posOnWindow.x = (int);
        posOnTexture.x = (int);
        posOnWindow.y = (int);
        posOnTexture.y = (int);
        posOnWindow.w = (int);
        posOnTexture.w = (int);
        posOnWindow.h = (int);
        posOnTexture.h = (int);*/
    }
}

runner::~runner()
{

}

void runner::HandleEvents(SDL_Event &e)
{
    if(mode==1)
    {

    }
}

void runner::update()
{
    //posOnWindow = Map::convertPos(pos);
}
