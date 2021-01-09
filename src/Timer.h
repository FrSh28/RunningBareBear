//
// Created by 劉瑄穎 on 2021/1/9.
//

#ifndef TIMER_H
#define TIMER_H
#include"BasicObject.h"
#include<cstdio>
#include<string>
#include"Files.h"


class Timer:public BasicObject
{
private:
    //The time game continue
    Uint32 gametime;
    //The timepassed
    Uint32 timepassed;
    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;

    //Timer Texture
    SDL_Texture* timerTexture;
    int texturewidth;
    int textureheight;

    //Background Texture
    SDL_Texture* background;
    int backgroundwidth;
    int backgroundheight;

    //Font
    TTF_Font * timerFont;

    //Load font
    bool loadTimerFont();

    //Load background image
    bool loadBackground();
    void closetimer();

    //Timer
    Uint32 getticks();

public:
    //Initializes variables
    Timer();
    ~Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();


    //Gets the timer's time
    Uint32 getTicks();

    bool handleEvents(SDL_Event& e);
    bool update();
};


#endif //SRC_TIMER_H
