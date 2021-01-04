#include "includeSDL.h"
#include "Game.h"
#include "Hunter.h"
#include <iostream>
#include <cmath>

Hunter::Hunter() :
	HunterSpeed(0), deltaX(0), deltaY(0), findX(0), findY(0), a(0), b(0), gameover(false), rememberX(0), rememberY(0),
	up_d(0), down_d(0), right_d(0), left_d(0)
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
		up.x = HunterPosOnMap.x;
		up.y = HunterPosOnMap.y - 1;
		down.x = HunterPosOnMap.x;
		down.y = HunterPosOnMap.y + 1;
		right.x = HunterPosOnMap.x + 1;
		right.y = HunterPosOnMap.y;
		left.x = HunterPosOnMap.x - 1;
		left.y = HunterPosOnMap.y;
		
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

enum direction
{
	UP, DOWN, RIGHT, LEFT 
}direct;

void Hunter::Chase()
{
	up_d    = pow((rememberX -    up.x), 2) + pow((rememberY -    up.y), 2);
	down_d  = pow((rememberX -  down.x), 2) + pow((rememberY -  down.y), 2);
	right_d = pow((rememberX - right.x), 2) + pow((rememberY - right.y), 2);
	left_d  = pow((rememberX -  left.x), 2) + pow((rememberY -  left.y), 2);
	
	direct = UP;
	minimum = up_d;
	if(down_d < minimum){
		minimum = down_d;
		direct = DOWN;
	}
	if(right_d < minimum){
		minimum = right_d;
		direct = RIGHT;
	}
	if(left_d < minimum){
		minimum = left_d;
		direct = LEFT;
	}
	switch(direct)
	{
		case UP   : break;
		case DOWN : break;
		case RIGHT: break;
		case LEFT : break;
	}
}

void Hunter::Stage1()
{
	Hvelocity = Run;
	Discovered = true; //will become false if Stage2 && Hunter go to an intersection && !RunnerVisible 
	rememberX = R_get_Xpos_on_map();
	rememberY = R_get_Ypos_on_map();
	Chase();
	//remembered the runner's position
	//run to the runner
}

void Hunter::Stage2()
{
	Hvelocity = Run;
	Chase();
	
	//run to the place where Stage1 remember
		//if it is an intersection
			//if !RunnerVisible --> Discovered = false
			//else Stage 1 (or do nothing?)
		//if it is corner
			//keep running until it's intersection
		
}

void Hunter::Stage3()
{
	Hvelocity = Walk;
}

bool Hunter::GameOver()
{
	gameover = false;
	a = R_get_Xpos_on_map() - HunterPosOnMap.x;
	b = R_get_Ypos_on_map() - HunterPosOnMap.y;
	if(abs(a) == 0 && abs(b) == 0)	   
	{
		gameover = true;   	
   }
	return gameover;
}

bool Hunter::RunnerVisible()
{	
	visible = true;
	a = R_get_Xpos_on_map() - HunterPosOnMap.x;
	b = R_get_Ypos_on_map() - HunterPosOnMap.y;
	deltaX = a / (a+b);
	deltaY = b / (a+b);	
	findX = HunterPosOnMap.x;
	findY = HunterPosOnMap.y;
	while(abs(findX - R_get_Xpos_on_map()) >= 1 || abs(findY - R_get_Ypos_on_map()) >= 1)
	{
		findX += deltaX;
		findY += deltaY;
		if(WhatsOnTheMap(round(findX), round(findY)) == WALL)
			visible = false;
	}
	return visible;
}
