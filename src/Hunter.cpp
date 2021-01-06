#include "includeSDL.h"
#include "Game.h"
#include "Hunter.h"
#include <iostream>
#include <cmath>

Hunter::Hunter() :
	HunterSpeed(0), gameover(false), arrive(false), SetSuccess(false), a(0), b(0), deltaX(0), deltaY(0), findX(0), findY(0)
{
	HunterPosOnMap = Set();
	Game &game = Game::GetGame();
	game.pushLayer(new hunterLayer);
}

SDL_Point Hunter::Set()		// Map will handle this --by FrSh
{
	SetSuccess = false;
	SDL_Point SetPos;
	while(!SetSuccess)
	{
		Game &game = Game::GetGame();
		SetPos.x = game.rdEngine()%(getMapWidth()); 
		srand(time(0));
		SetPos.y = game.rdEngine()%(getMapHeight());
		if(WhatsOnTheMap(SetPos.x,SetPos.y) == EMPTY) 
		{
			SetSuccess = true;
			return SetPos;
		} 
	}
}
Hunter::~Hunter()
{
	
}

void Hunter::handleEvents(SDL_Event &e)
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
		{
			visible = false;
			break;
		}
	}
	return visible;
}



void Hunter::Stage1()
{
	Hvelocity = Run;
	Discovered = true; 
	//every 60 frames
	directPos.x = R_get_Xpos_on_map();
	directPos.y = R_get_Ypos_on_map();
	HaveFound = false;
	Chase(HunterPosOnMap, directPos);
	
	
}

void Hunter::Stage2()
{
	Hvelocity = Run;
	if(!HaveFound)
	{
		HaveFound = true;
		Chase(HunterPosOnMap, directPos);
	}
	if(Arrive())
	{
		Discovered = false;
		Stage3();	
	}	
}

void Hunter::Stage3()
{
	Hvelocity = Walk;
	if(Arrive())
	{
		directPos = Set();
		HaveFound = false;
	}
	if(!HaveFound)
	{
		HaveFound = true;
		Chase(HunterPosOnMap, directPos);
	}
	
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
		Node(const Node &x){}
	};
	
	std::queue<Node> q; //
	Node init; 
	init.step = 0;
	init.way.push_back(HunterPosOnMap);  
	visited[HunterPosOnMap.x][HunterPosOnMap.y];
	q.push(init);
	while(!q.empty())
	{
		Node curNode = q.front(); //
		q.pop();
		SDL_Point curP = curNode.way.back();
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
					go.push(curNode.way[i]);
				}
				break;
			}
			else
			{
				visited[curP.x + 1][curP.y] = true;
				Node tmp;
				tmp.step = curNode.step + 1;
				for(int i=0; i<tmp.step; i++)
				{
					tmp.way.push_back(curNode.way[i]);
				}
				SDL_Point add;
				add.x = curP.x + 1;
				add.y = curP.y;
				tmp.way.push_back(add);
				q.push(tmp);
			}
		}
		//left
		if(WhatsOnTheMap(curP.x - 1, curP.y) != WALL && !visited[curP.x - 1][curP.y])
		{
			if(curP.x - 1 == directPos.x && curP.y == directPos.y)
			{
				while(!go.empty())
				{
					go.pop();
				}
				for(int i=0; i<step; i++)
				{
					go.push(curNode.way[i]);
				}
				break;
			}
			else
			{
				visited[curP.x - 1][curP.y] = true;
				Node tmp;
				tmp.step = curNode.step + 1;
				for(int i=0; i<step; i++)
				{
					tmp.way.push_back(curNode.way[i]);
				}
				SDL_Point add;
				add.x = curP.x - 1;
				add.y = curP.y;
				tmp.way.push_back(add);
				q.push(tmp);
			}
		}
		//down
		if(WhatsOnTheMap(curP.x, curP.y + 1) != WALL && !visited[curP.x][curP.y + 1])
		{
			if(curP.x == directPos.x && curP.y + 1 == directPos.y)
			{
				while(!go.empty())
				{
					go.pop();
				}
				for(int i=0; i<step; i++)
				{
					go.push(curNode.way[i]);
				}
				break;				
			}
			else
			{
				visited[curP.x][curP.y + 1] = true;
				Node tmp;
				tmp.step = curNode.step + 1;
				for(int i=0; i<step; i++)
				{
					tmp.way.push_back(curNode.way[i]);
				}
				SDL_Point add;
				add.x = curP.x;
				add.y = curP.y + 1;
				tmp.way.push_back(add);
				q.push(tmp);
			}
		}
		//up
		if(WhatsOnTheMap(curP.x, curP.y - 1) != WALL && !visited[curP.x][curP.y - 1])
		{
			if(curP.x == directPos.x && curP.y - 1 == directPos.y)
			{
				while(!go.empty())
				{
					go.pop();
				}
				for(int i=0; i<step; i++)
				{
					go.push(curNode.way[i]);
				}
				break;				
			}
			else
			{
				visited[curP.x][curP.y - 1] = true;
				Node tmp;
				tmp.step = curNode.step + 1;
				for(int i=0; i<step; i++)
				{
					tmp.way.push_back(curNode.way[i]);
				}
				SDL_Point add;
				add.x = curP.x;
				add.y = curP.y - 1;
				tmp.way.push_back(add);
				q.push(tmp);
			}
		}
	}
	while(!q.empty())
	{
		delete q.front();
		q.pop();
	}
}

