#include "includeSDL.h"
#include "Game.h"
#include "Hunter.h"
#include <iostream>
#include <cmath>

Hunter::Hunter(SDL_Point MapPos, SDL_Point PixelPos) :
	HunterSpeed(0), gameover(false), arrive(false), SetSuccess(false), a(0), b(0), deltaX(0), deltaY(0), findX(0), findY(0)
	map(&Map::getMap())
{
	setMapPos(MapPos);
	setPixelPos(PixelPos);
	directPos = HunterPixelPos;
}

void Hunter::setMapPos(SDL_Point &MapPos)
{
	HunterMapPos = MapPos;
}

void Hunter::setPixelPos(SDL_Point &PixelPos)
{
	HunterCenterPixel = PixelPos;
	HunterPixelPos.x = HunterCenterPixel.x  - HunterWidth/2;
	HunterPixelPos.y = HunterCenterPixel.y - HunterHeight/2;
}


Hunter::~Hunter()
{
	
}

bool Hunter::handleEvents(SDL_Event &e)
{
	
}

void Hunter::update()
{
	HunterCenterPixel.x = HunterPixelPos.x + HunterWidth/2;
	HunterCenterPixel.y = HunterPixelPos.y + HunterHeight/2;
	HunterMapPos = map->pixelPosTomapPos(HunterCenterPixel);
	RunnerMapPos = map->getRunnerMapPos();
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
	rectOnTexture = SDL_Rect({ , , , });
}

bool Hunter::RunnerVisible()
{	
	visible = true;
	a = RunnerMapPos.x - HunterMapPos.x;
	b = RunnerMapPos.y - HunterMapPos.y;
	deltaX = a / (a+b);
	deltaY = b / (a+b);	
	findpos = HunterMapPos;
	findX = HunterMapPos.x;
	findY = HunterMapPos.y;
	while(findpos != RunnerMapPos )
	{
		findX += deltaX;
		findY += deltaY;
		findpos.x = round(findX);
		findpos.y = round(findY);
		if(map->isWall(findpos))
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
	directPos = RunnerMapPos;
	Chase(HunterMapPos, directPos);
	NextPixel = map->mapPosTopixelPos(HunterMapPos);
	//
	//change HunterPixelPos
	Move();
}

void Hunter::Stage2()
{
	Hvelocity = Run;
	if(Arrive(directPos))
	{
		Discovered = false;
		Stage3();	
	}
	else
	{
		Move();
	}	
}

void Hunter::Stage3()
{
	Hvelocity = Walk;
	if(Arrive(directPos))
	{
		directPos = Set();
		HaveFound = false;
		Chase(HunterMapPos, directPos);
		NextPixel = map->mapPosTopixelPos(HunterMapPos);
	}
	Move();
}

void Hunter::Move()
{
	if(Arrive(NextPixel))
	{
		NextPixel = map->mapPosTopixelPos(go.front());
		go.pop;
	}	
	else
	{
		if(HunterPixelPos.x < NextPixel.x)
		{
			HunterPixelPos.x += Hvelocity;
		}
		else if(HunterPixelPos.x > NextPixel.x)
		{
			HunterPixelPos.x -= Hvelocity;
		}
		else
		{
			if(HunterPixelPos.y < NextPixel.y)
			{
				HunterPixelPos.y += Hvelocity;
			}
			else
			{
				HunterPixelPos.y -= Hvelocity;
			}
		}
	}
}

SDL_Point Hunter::Set()		
{
	SetSuccess = false;
	SDL_Point SetPos;
	while(!SetSuccess)
	{
		Game &game = Game::GetGame();
		SetPos.x = game.rdEngine()%(map->getRowNum()); 
		SetPos.y = game.rdEngine()%(map->getColNum());
		if(map->isSpace(SetPos)) 
		{
			SetSuccess = true;
			return SetPos;
		} 
	}
}
bool Hunter::Arrive(SDL_Point destination)
{
	arrive = false;
	if(HunterPixelPos == destination)
	{
		arrive = true;
	}
	return arrive;
}

void Hunter::Chase(SDL_Point HunterMapPos, SDL_Point directPos)
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
	init.way.push_back(HunterMapPos);  
	visited[HunterMapPos.x][HunterMapPos.y];
	q.push(init);
	
	while(!q.empty())
	{
		Node curNode = q.front(); //
		q.pop();
		SDL_Point curP = curNode.way.back();
		
		//right
		SDL_Point nextP;
		nextP.x = curP.x + 1;
		nextP.y = curP.y;
		if(!(map->isWall(nextP)) && !(visited[nextP.x][nextP.y]))
		{
			visited[nextP.x][nextP.y] = true;
			Node tmp;
			tmp.step = curNode.step + 1;
			for(int i=0; i<tmp.step; i++)
			{
				tmp.way.push_back(curNode.way[i]);
			}
			tmp.way.push_back(nextP);
			
			if(nextP == directPos)
			{
				while(!go.empty())
				{
					go.pop();
				}
				for(int i=0; i<=tmp.step; i++)
				{
					go.push(tmp.way[i]);
				}
				break;
			}
			else
			{
				q.push(tmp);
			}
		}
		
		//left
		SDL_Point nextP;
		nextP.x = curP.x - 1;
		nextP.y = curP.y;
		if(!(map->isWall(nextP)) && !(visited[nextP.x][nextP.y]))
		{
			visited[nextP.x][nextP.y] = true;
			Node tmp;
			tmp.step = curNode.step + 1;
			for(int i=0; i<tmp.step; i++)
			{
				tmp.way.push_back(curNode.way[i]);
			}
			tmp.way.push_back(nextP);
			
			if(nextP == directPos)
			{
				while(!go.empty())
				{
					go.pop();
				}
				for(int i=0; i<=tmp.step; i++)
				{
					go.push(tmp.way[i]);
				}
				break;
			}
			else
			{
				q.push(tmp);
			}
		}
		
		//down
		SDL_Point nextP;
		nextP.x = curP.x;
		nextP.y = curP.y + 1;
		if(!(map->isWall(nextP)) && !(visited[nextP.x][nextP.y]))
		{
			visited[nextP.x][nextP.y] = true;
			Node tmp;
			tmp.step = curNode.step + 1;
			for(int i=0; i<tmp.step; i++)
			{
				tmp.way.push_back(curNode.way[i]);
			}
			tmp.way.push_back(nextP);
			
			if(nextP == directPos)
			{
				while(!go.empty())
				{
					go.pop();
				}
				for(int i=0; i<=tmp.step; i++)
				{
					go.push(tmp.way[i]);
				}
				break;
			}
			else
			{
				q.push(tmp);
			}
		}
		
		//up
		SDL_Point nextP;
		nextP.x = curP.x;
		nextP.y = curP.y - 1;
		if(!(map->isWall(nextP)) && !(visited[nextP.x][nextP.y]))
		{
			visited[nextP.x][nextP.y] = true;
			Node tmp;
			tmp.step = curNode.step + 1;
			for(int i=0; i<tmp.step; i++)
			{
				tmp.way.push_back(curNode.way[i]);
			}
			tmp.way.push_back(nextP);
			
			if(nextP == directPos)
			{
				while(!go.empty())
				{
					go.pop();
				}
				for(int i=0; i<=tmp.step; i++)
				{
					go.push(tmp.way[i]);
				}
				break;
			}
			else
			{
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
/*
if(!(map->isWall(nextP)) && !visited[nextP.x][nextP.y])
		{
			if(nextP == directPos)
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
				visited[nextP.x][nextP.y] = true;
				Node tmp;
				tmp.step = curNode.step + 1;
				for(int i=0; i<step; i++)
				{
					tmp.way.push_back(curNode.way[i]);
				}
				tmp.way.push_back(nextP);
				q.push(tmp);
			}
		}
*/

