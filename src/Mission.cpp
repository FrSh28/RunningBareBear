#include <iostream>
#include <string>
#include "includeSDL.h"
#include "Game.h"
#include "Layer.h"
#include "Mission.h"
#include "UserEvent.h"
using namespace std;

MissionTypes curMission = MissionTotal;

Mission :: Mission(string _name)
 : BasicObject(_name)
{
	success = false;
	//posOnWindow->x = ;
	//posOnWindow->y = ;
	//posOnWindow->w = ;
	//posOnWindow->h = ;
	//posOnTexture->x = ;
	//posOnTexture->y = ;
	//posOnTexture->w = ;
	//posOnTexture->h = ;
}
Mission :: ~Mission() //call when mission is complete or timeover ,Current_Mission = 0
{ }

Mission *createMission(MissionTypes choice)
{
	
	switch (choice) //somewhere : srand(time(0)); CreateMission(rand()%MissionTotal);
	{
		case Mission1Type1:
			return new Mission1_1();
		case Mission1Type2:
			return new Mission1_2();
		case Mission1Type3:
			return new Mission1_3();
		case Mission2Type1:
			return new Mission2_1();
		case Mission2Type2:
			return new Mission2_2();
		case Mission2Type3:
			return new Mission2_3();			

	}
}


Mission1_1 :: Mission1_1 ()
 : Mission("Mission 1 ")
{
	curMission = Mission1Type1;
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission1_1 :: ~Mission1_1 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

bool Mission1_1 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < posOnWindow->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < posOnWindow->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushOverlayer(new missionLayer);
		}
	}
	else if(e.type == USE) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

void Mission1_1 :: update()
{
	//什麼都沒有的樣子 
}


Mission1_2 :: Mission1_2 ()
 : Mission("Mission 1 ")
{
	curMission = Mission1Type2;
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission1_2 :: ~Mission1_2 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

bool Mission1_2 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < posOnWindow->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < posOnWindow->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushOverlayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

void Mission1_2 :: update()
{
	//什麼都沒有的樣子 
}

Mission1_3 :: Mission1_3 ()
 : Mission("Mission 1 ")
{
	curMission = Mission1Type3;
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission1_3 :: ~Mission1_3 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

bool Mission1_3 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < posOnWindow->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < posOnWindow->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushOverlayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

void Mission1_3 :: update()
{
	//什麼都沒有的樣子 
}


Mission2_1 :: Mission2_1 ()
 : Mission("Mission 2 ")
{
	curMission = Mission2Type1;
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission2_1 :: ~Mission2_1 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

bool Mission2_1 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < posOnWindow->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < posOnWindow->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushOverlayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

void Mission2_2 :: update()
{
	//什麼都沒有的樣子 
}


Mission2_2 :: Mission2_2 ()
 : Mission("Mission 2 ")
{
	curMission = Mission2Type2;
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission2_1 :: ~Mission2_2 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

bool Mission2_2 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < posOnWindow->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < posOnWindow->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushOverlayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

void Mission2_2 :: update()
{
	//什麼都沒有的樣子 
}

Mission2_3 :: Mission2_3 ()
 : Mission("Mission 2 ")
{
	curMission = Mission2Type3;
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission2_3 :: ~Mission2_3 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

bool Mission2_3 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < posOnWindow->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < posOnWindow->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushOverlayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

void Mission2_3 :: update()
{
	//什麼都沒有的樣子 
}


/*

if (MISSION != ((Uint32)-1)) {
    SDL_Event event;
    SDL_zero(event);
	event.type = Pick_Up;
    event.user.code = mission_code;
    event.user.data1 = significant_data1;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
}
*/
