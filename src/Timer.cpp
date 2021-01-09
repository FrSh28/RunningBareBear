//
// Created by 劉瑄穎 on 2021/1/9.
//

#include "Timer.h"
TTF_Font* TimerFont = NULL;
SDL_Renderer* TimerRenderer = NULL;
Timer::Timer():gametime(300000), backgroundwidth(), backgroundheight(),mPaused(false),mStarted(false)
{
    loadTimerFont();

    rectOnScreen.x = ;
    rectOnScreen.y = 0;
    rectOnScreen.w = ;
    rectOnScreen.h = ;

    rectOnTexture.x = ;
    rectOnTexture.y = ;
    rectOnTexture.w = ;
    rectOnTexture.h = ;
}

Timer::~Timer()
{
    closetimer();
}

void Timer::start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void Timer::stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

    //Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}
void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( mStarted && !mPaused )
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}
void Timer::unpause()
{
    //If the timer is running and paused
    if( mStarted && mPaused )
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 Timer::getticks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if( mStarted )
    {
        //If the timer is paused
        if( mPaused )
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

bool Timer::handleEvents(SDL_Event& e)
{}
bool Timer::update()
{
    this->timepassed = getticks();

    return true;
}


//private function
bool Timer::loadTimerFont()
{
    bool success = true;
    timerFont = TTF_OpenFont( "fonts/octin college rg.ttf", 28 );
    if( timerFont == NULL )
    {
        printf( "Failed to load timer font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Set text color as black
        SDL_Color timertextColor = { 0, 0, 0, 255 };
    }
    return success;
}

bool Timer::loadBackground()
{
    bool success = true;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( "../image/" );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        background = SDL_CreateTextureFromSurface(TimerRenderer, loadedSurface);
        if (background == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", SDL_GetError());
        }
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return success;
}

Uint32 Timer::getTicks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if( mStarted )
    {
        //If the timer is paused
        if( mPaused )
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

void Timer::closetimer()
{
    //Free loaded images
    if( timerTexture != NULL )
    {
        SDL_DestroyTexture( timerTexture );
        timerTexture = NULL;
    }

    //Free global font
    if(timerFont!=NULL)
    {
        TTF_CloseFont( timerFont );
        timerFont = NULL;
    }
}


