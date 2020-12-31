#include <iostream>
#include <string>
#include "includeSDL.h"
#include "Game.h"
#include "Layer.h"
#include "Mission.h"
using namespace std;

MISSION = SDL_RegisterEvents(0);

Mission :: Mission() :
	name(NULL), texture(NULL), posOnWindow(NULL), posOnTexture(NULL)
{ 
	//posOnWindow->x = ;
	//posOnWindow->y = ;
	//posOnWindow->w = ;
	//posOnWindow->h = ;
	//posOnTexture->x = ;
	//posOnTexture->y = ;
	//posOnTexture->w = ;
	//posOnTexture->h = ;
}
Mission :: ~Mission() //call when mission is complete or timeover 
{ }

Mission *CreateMission(int choice)
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
 : name("任務1 "), texture(NULL), success(false)
{
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission1_1 :: ~Mission1_1 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

Mission1_1 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < mPosition->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < mPosition->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushLayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

Mission1_1 :: update()
{
	//什麼都沒有的樣子 
}


Mission1_2 :: Mission1_2 ()
 : name("任務1 "), texture(NULL), success(false)
{
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission1_2 :: ~Mission1_2 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

Mission1_2 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < mPosition->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < mPosition->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushLayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

Mission1_2 :: update()
{
	//什麼都沒有的樣子 
}

Mission1_3 :: Mission1_3 ()
 : name("任務1 "), texture(NULL), success(false)
{
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission1_3 :: ~Mission1_3 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

Mission1_3 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < mPosition->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < mPosition->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushLayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

Mission1_3 :: update()
{
	//什麼都沒有的樣子 
}


Mission2_1 :: Mission2_1 ()
 : name("任務2 "), texture(NULL), success(false)
{
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission2_1 :: ~Mission2_1 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

Mission2_1 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < mPosition->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < mPosition->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushLayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

Mission2_2 :: update()
{
	//什麼都沒有的樣子 
}


Mission2_2 :: Mission2_2 ()
 : name("任務2 "), texture(NULL), success(false)
{
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission2_1 :: ~Mission2_2 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

Mission2_2 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < mPosition->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < mPosition->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushLayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

Mission2_2 :: update()
{
	//什麼都沒有的樣子 
}

Mission2_3 :: Mission2_3 ()
 : name("任務2 "), texture(NULL), success(false)
{
	Game &game = Game::GetGame();
	//game.Map.addItem();                    
	//texture = loadMedia(TEXTURE_MISSION);	
}

Mission2_3 :: ~Mission2_3 ()
{
	//releaseMedia(TEXTURE_MISSION);
	texture = NULL;
}

Mission2_3 :: handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		int X, Y;
        SDL_GetMouseState( &X, &Y );

        bool inside = true; 
        if( X < mPosition->x || X > posOnWindow->x + posOnWindow->w){
            inside = false;
        }    
        else if( Y < mPosition->y || Y > posOnWindow->y + posOnWindow->h ){
            inside = false;
        }
        
        if(inside)
        {
        	Game &game = Game::GetGame();
			game.pushLayer(new missionLayer);
		}
	}
	else if(e.type == MISSION) //可能是按下E鍵之類的 
		{
			if(e.user.code == Mission1Type1)
			success = true;
		}
}

Mission2_3 :: update()
{
	//什麼都沒有的樣子 
}


/*

if (MISSION != ((Uint32)-1)) {
    SDL_Event event;
    SDL_zero(event);
	event.type = Mission;
    event.user.code = mission_code;
    event.user.data1 = significant_data1;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
}
*/
