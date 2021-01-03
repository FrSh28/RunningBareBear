#include "includeSDL.h"
#include "Game.h"
#include "Hunter.h"
#include <iostream>
#include <cmath>

Hunter::Hunter() :
	HunterSpeed(0)
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
	if(abs(HunterPosOnMap.x - getRunnerPos_XOnMap()) <= Size && 
	   abs(HunterPosOnMap.y - getRunnerPos_YOnMap()) <= Size)
	   {
			gameover = true;   	
	   }
	return gameover;
}

bool Hunter::RunnerVisible()
{
	bool visible = false;
	int temp;
	if(abs(HunterPosOnMap.x - getRunnerPos_XOnMap()) <= Size)
	{
		visible = true;
		temp = HunterPosOnMap.y - HunterPosOnMap.y % Size;
		
		if(HunterPosOnMap.y < getRunnerPos_YOnMap()) 
		//such as Hunter(900,710) Runner(846,950) it will find out whether (900,700) (900,800) (900,900) have wall(if Size=100)
		{
			for(int i=temp; i<=getRunnerPos_YOnMap(); i+=Size) //size is how big a wall or object is
			{
				if(WhatsOnTheMap(HunterPosOnMap.x,i) == WALL)
					visible = false;
			}
		}
		else
		{
			for(int i=temp;i>=HunterPosOnMap.y;i-=Size) //size is how big a wall or object is
			{
				if(WhatsOnTheMap(i,HunterPosOnMap.y) == WALL)
					visible = false;
			}
		}
	}
	if(abs(HunterPosOnMap.y - getRunnerPos_YOnMap()) <= Size)
	{
		visible = false;
		temp = HunterPosOnMap.x - HunterPosOnMap.x % Size;
		
		if(HunterPosOnMap.x < getRunnerPos_XOnMap())
		{
			for(int i=temp; i<=getRunnerPos_XOnMap(); i+=Size) //size is how big a wall or object is
			{
				if(WhatsOnTheMap(i,HunterPosOnMap.y) == WALL)
					visible = false;
			}
		}
		else
		{
			for(int i=temp; i<=HunterPosOnMap.y; i-=Size) //size is how big a wall or object is
			{
				if(WhatsOnTheMap(i,HunterPosOnMap.y) == WALL)
					visible = false;
			}
		}
	}
	return visible;
}
