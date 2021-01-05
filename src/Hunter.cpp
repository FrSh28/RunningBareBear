#include "includeSDL.h"
#include "Game.h"
#include "Hunter.h"
#include <iostream>
#include <cmath>

Hunter::Hunter() :
	HunterSpeed(0), gameover(false), arrive(false), SetSuccess(false), a(0), b(0), deltaX(0), deltaY(0), findX(0), findY(0)
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

enum direction
{
	UP, DOWN, RIGHT, LEFT 
}direct;

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

void Hunter::Chase(SDL_Point HunterPosOnMap, SDL_Point directPos)
{
	bool visited[row][col];
	for(int i=0; i<row; i++)
	for(int j=0; j<col; J++)
	visited[i][j] = false;
	
	class Node
	{
	public:
		int step;
		std::vector<SDL_Point> way;
		Node(){} 
		~Node(){}
	};
	
	std::queue<Node*> q; 
	Node* init = new Node; 
	init->step = 0;
	init->way.push_back(HunterPosOnMap);  
	q.push(init);
	while(!q.empty())
	{
		Node* curNode = q.front(); 
		q.pop();
		SDL_Point curP = curNode->way.back();
		//right
		if(WhatsOnTheMap(curP.x + 1, curP.y) != WALL && !visited[curP.x + 1][curP.y])
		{
			if(curP.x + 1 == directPos.x && curP.y == directPos.y)
			{
				while(!go.empty())
				{
					go.pop();
				}
				for(int i=0; i<step; i++)
				{
					go.push(curNode->way[i]);
				}
				break;
			}
			else
			{
				visited[curP.x + 1][curP.y] = true;
				Node* tmp = new Node;
				tmp->step = curNode->step + 1;
				for(int i=0; i<step; i++)
				{
					tmp->way.push_back(curNode->way[i]);
				}
				SDL_Point add;
				add.x = curP.x + 1;
				add.y = curP.y;
				tmp->way.push_back(add);
				q.push(tmp);
			}
		}
		//left
		if(WhatsOnTheMap(curP.x - 1, curP.y) != WALL && !visited[curP.x - 1][curP.y])
		{
			if(curP.x - 1 == directPos.x && curP.y == directPos.y)
			{
				
			}
			else
			{
				visited[curP.x - 1][curP.y] = true;
				Node* tmp = new Node;
				tmp->step = curNode->step + 1;
				for(int i=0; i<step; i++)
				{
					tmp->way.push_back(curNode->way[i]);
				}
				SDL_Point add;
				add.x = curP.x - 1;
				add.y = curP.y;
				tmp->way.push_back(add);
				q.push(tmp);
			}
		}
		//down
		if(WhatsOnTheMap(curP.x, curP.y + 1) != WALL && !visited[curP.x][curP.y + 1])
		{
			if(curP.x == directPos.x && curP.y + 1 == directPos.y)
			{
				
			}
			else
			{
				visited[curP.x][curP.y + 1] = true;
				Node* tmp = new Node;
				tmp->step = curNode->step + 1;
				for(int i=0; i<step; i++)
				{
					tmp->way.push_back(curNode->way[i]);
				}
				SDL_Point add;
				add.x = curP.x;
				add.y = curP.y + 1;
				tmp->way.push_back(add);
				q.push(tmp);
			}
		}
		//up
		if(WhatsOnTheMap(curP.x, curP.y - 1) != WALL && !visited[curP.x][curP.y - 1])
		{
			if(curP.x == directPos.x && curP.y - 1 == directPos.y)
			{
				
			}
			else
			{
				visited[curP.x][curP.y - 1] = true;
				Node* tmp = new Node;
				tmp->step = curNode->step + 1;
				for(int i=0; i<step; i++)
				{
					tmp->way.push_back(curNode->way[i]);
				}
				SDL_Point add;
				add.x = curP.x;
				add.y = curP.y - 1;
				tmp->way.push_back(add);
				q.push(tmp);
			}
		}
		delete curNode;
	}
	while(!q.empty())
	{
		delete q.front();
		q.pop();
	}
	
	

}


void Hunter::Stage1()
{
	Hvelocity = Run;
	Discovered = true; //will become false if Stage2 && Hunter go to an intersection && !RunnerVisible 
	//every 60 frame
	directPos.x = R_get_Xpos_on_map();
	directPos.y = R_get_Ypos_on_map();
	Chase(HunterPosOnMap, directPos);
	
}

void Hunter::Stage2()
{
	Hvelocity = Run;
	Chase(HunterPosOnMap, directPos);
	if(Arrive())
	{
		if(!RunnerVisible())
	}
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
bool Hunter::Arrive()
{
	arrive = false;
	if(HunterPosOnMap.x == directPos.x && HunterPosOnMap.y == directPos.y)
	{
		arrive = true;
	}
	return arrive;
}
// PosOnMap.x = (PosOnWindow.x + 0.5*w) / 50
 

