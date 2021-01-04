#include "includeSDL.h"
#include "Game.h"
#include "Hunter.h"
#include <iostream>
#include <cmath>

Hunter::Hunter() :
	HunterSpeed(0), deltaX(0), deltaY(0), findX(0), findY(0), a(0), b(0)
{
	SetSuccess = false;
	while(!SetSuccess)
	{
		srand(time(0));
		HunterPosOnMap.x = rand()%(getMapWidth()); 
		srand(time(0));
		HunterPosOnMap.y = rand()%(getMapHeight());
		if(WhatsOnTheMap(HunterPosOnMap.x,HunterPosOnMap.y) == EMPTY) //EMPTY(a number) represent [HunterPosOnMap.x][HunterPosOnMap.y] is empty 
		{
			SetSuccess = true;
			//may need to set [HunterPosOnMap.x][HunterPosOnMap.y] into HUNTER(a number)
			Game &game = Game::GetGame();
			game.pushLayer(new hunterLayer);
		} 
		//getMapWidth() and getMapHeight() are just temporary name, used to return how many matrixs do map have.
	}
}
//somewhere set initial walk direction
Hunter::~Hunter()
{
	
}

bool Hunter::handleEvents(SDL_Event &e)
{
	
}

void Hunter::update()
{
	if(GameOver())
	{
		//...	
	} 
	else
	{
		if(RunnerVisible())
		{
			Stage1();
		}
		else
		{
			if(Discovered)
			{
				Stage2();
			}
			else
			{
				Stage3();
			}
		}
		
	}
}
void Hunter::Stage1()
{
	HunterSpeed = HunterRun;
	Discovered = true; //will become false if Stage2 && Hunter go to an intersection && !RunnerVisible 
	
	//remembered the runner's position
	//run to the runner
}

void Hunter::Stage2()
{
	HunterSpeed = HunterRun;
	//run to the place where Stage1 remember
		//if it is an intersection
			//if !RunnerVisible --> Discovered = false
			//else Stage 1 (or do nothing?)
		//if it is corner
			//keep running until it's intersection
		
}

void Hunter::Stage3()
{
	HunterSpeed = HunterWalk;
}

bool Hunter::GameOver()
{
	bool gameover = false;
	a = getRunnerPos_XOnMap() - HunterPosOnMap.x;
	b = getRunnerPos_YOnMap() - HunterPosOnMap.y;
	if(abs(a) <= 1 && abs(b) <= 1)	   
	{
		gameover = true;   	
   }
	return gameover;
}

bool Hunter::RunnerVisible()
{	
	visible = true;
	a = getRunnerPos_XOnMap() - HunterPosOnMap.x;
	b = getRunnerPos_YOnMap() - HunterPosOnMap.y;
	deltaX = a / (a+b);
	deltaY = b / (a+b);	
	findX = HunterPosOnMap.x;
	findY = HunterPosOnMap.y;
	while(abs(findX - getRunnerPos_XOnMap()) >= 1 || abs(findY - getRunnerPos_YOnMap()) >= 1)
	{
		findX += deltaX;
		findY += deltaY;
		if(WhatsOnTheMap(round(findX), round(findY)) == WALL)
			visible = false;
	}
	return visible;
}
