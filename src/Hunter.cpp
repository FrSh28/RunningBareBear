#include "includeSDL.h"
#include "Game.h"
#include "Hunter.h"
#include "Map.h"
#include "UserEvent.h"
#include <queue>
#include <iostream>
#include <cmath>
SDL_Rect Hunter_Clip[TOTAL];

Hunter::Hunter(SDL_Point MapPos, SDL_Point PixelPos) :
	Hvelocity(0), arrive(false), SetSuccess(false), a(0), b(0), deltaX(0), deltaY(0),
	findX(0), findY(0), Animation_Frames(3), Run(3), Walk(6), frame(0), map(&Map::getMap())
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
	return false;
}

bool Hunter::update()
{
	static int frame = 0;
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
	rectOnTexture = Hunter_Clip[direction+frame/updateRate];
	frame ++;
	if(frame/updateRate == Animation_Frames){frame=0;}
	//if it change return true
	return true;
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
	while(findpos.x != RunnerMapPos.x || findpos.x != RunnerMapPos.x)
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
	updateRate = 3;
	Discovered = true; 
	//every 60 frames
	if(frame == 0)
	{
		directPos = RunnerMapPos;
		Chase(HunterMapPos, directPos);
		NextPixel = map->mapPosTopixelPos(HunterMapPos);
	}
	//
	Move();
}

void Hunter::Stage2()
{
	Hvelocity = Run;
	updateRate = 3;
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
	updateRate = 6;
	if(Arrive(directPos))
	{
		directPos = Set();
		Chase(HunterMapPos, directPos);
		NextPixel = map->mapPosTopixelPos(HunterMapPos);
	}
	Move();
}

bool Hunter::Arrive(SDL_Point destination)
{
	arrive = false;
	if(HunterPixelPos.x == destination.x && HunterPixelPos.y == destination.y)
	{
		arrive = true;
	}
	return arrive;
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
			direction = RIGHT_1;
		}
		else if(HunterPixelPos.x > NextPixel.x)
		{
			HunterPixelPos.x -= Hvelocity;
			direction = LEFT_1;
		}
		else
		{
			if(HunterPixelPos.y < NextPixel.y)
			{
				HunterPixelPos.y += Hvelocity;
				direction = DOWN_1;
			}
			else
			{
				HunterPixelPos.y -= Hvelocity;
				direction = UP_1;
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

void Hunter::Chase(SDL_Point HunterMapPos, SDL_Point directpos)
{
	bool visited[map->getRowNum()][map->getColNum()];
	for(int i=0; i<map->getRowNum(); i++)
	for(int j=0; j<map->getColNum(); j++)
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
	visited[HunterMapPos.x][HunterMapPos.y] = true;
	q.push(init);
	
	while(!q.empty())
	{
		Node curNode = q.front(); //
		q.pop();
		SDL_Point curP = curNode.way.back();
		
		//right
		SDL_Point nextP1;
		nextP1.x = curP.x + 1;
		nextP1.y = curP.y;
		if(!(map->isWall(nextP1)) && !(visited[nextP1.x][nextP1.y]))
		{
			visited[nextP1.x][nextP1.y] = true;
			Node tmp;
			tmp.step = curNode.step + 1;
			for(int i=0; i<tmp.step; i++)
			{
				tmp.way.push_back(curNode.way[i]);
			}
			tmp.way.push_back(nextP1);
			
			if(nextP1.x == directpos.x && nextP1.y == directpos.y)
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
		SDL_Point nextP2;
		nextP2.x = curP.x - 1;
		nextP2.y = curP.y;
		if(!(map->isWall(nextP2)) && !(visited[nextP2.x][nextP2.y]))
		{
			visited[nextP2.x][nextP2.y] = true;
			Node tmp;
			tmp.step = curNode.step + 1;
			for(int i=0; i<tmp.step; i++)
			{
				tmp.way.push_back(curNode.way[i]);
			}
			tmp.way.push_back(nextP2);
			
			if(nextP2.x == directpos.x && nextP2.y == directpos.y)
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
		SDL_Point nextP3;
		nextP3.x = curP.x;
		nextP3.y = curP.y + 1;
		if(!(map->isWall(nextP3)) && !(visited[nextP3.x][nextP3.y]))
		{
			visited[nextP3.x][nextP3.y] = true;
			Node tmp;
			tmp.step = curNode.step + 1;
			for(int i=0; i<tmp.step; i++)
			{
				tmp.way.push_back(curNode.way[i]);
			}
			tmp.way.push_back(nextP3);
			
			if(nextP3.x == directpos.x && nextP3.y == directpos.y)
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
		SDL_Point nextP4;
		nextP4.x = curP.x;
		nextP4.y = curP.y - 1;
		if(!(map->isWall(nextP4)) && !(visited[nextP4.x][nextP4.y]))
		{
			visited[nextP4.x][nextP4.y] = true;
			Node tmp;
			tmp.step = curNode.step + 1;
			for(int i=0; i<tmp.step; i++)
			{
				tmp.way.push_back(curNode.way[i]);
			}
			tmp.way.push_back(nextP4);
			
			if(nextP4.x == directpos.x && nextP4.y == directpos.y)
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
//UP_1, UP_2, UP_3, DOWN_1, DOWN_2, DOWN_3, RIGHT_1, RIGHT_2, RIGHT_3, LEFT_1, LEFT_2, LEFT_3, TOTAL
void Hunter::initHunter_Clips()                // init render Hunter_Clips
{
    //Up
    Hunter_Clip[UP_1].x = 0000;
    Hunter_Clip[UP_1].y = 0000;
    Hunter_Clip[UP_1].w = 0000;
    Hunter_Clip[UP_1].h = 0000;

    Hunter_Clip[UP_2].x = 0000;
    Hunter_Clip[UP_2].y = 0000;
    Hunter_Clip[UP_2].w = 0000;
    Hunter_Clip[UP_2].h = 0000;

    Hunter_Clip[UP_3].x = 0000;
    Hunter_Clip[UP_3].y = 0000;
    Hunter_Clip[UP_3].w = 0000;
    Hunter_Clip[UP_3].h = 0000;

    // Down
    Hunter_Clip[DOWN_1].x = 0000;
    Hunter_Clip[DOWN_1].y = 0000;
    Hunter_Clip[DOWN_1].w = 0000;
    Hunter_Clip[DOWN_1].h = 0000;

    Hunter_Clip[DOWN_2].x = 0000;
    Hunter_Clip[DOWN_2].y = 0000;
    Hunter_Clip[DOWN_2].w = 0000;
    Hunter_Clip[DOWN_2].h = 0000;

    Hunter_Clip[DOWN_3].x = 0000;
    Hunter_Clip[DOWN_3].y = 0000;
    Hunter_Clip[DOWN_3].w = 0000;
    Hunter_Clip[DOWN_3].h = 0000;

    //Right
    Hunter_Clip[RIGHT_1].x = 0000;
    Hunter_Clip[RIGHT_1].y = 0000;
    Hunter_Clip[RIGHT_1].w = 0000;
    Hunter_Clip[RIGHT_1].h = 0000;

    Hunter_Clip[RIGHT_2].x = 0000;
    Hunter_Clip[RIGHT_2].y = 0000;
    Hunter_Clip[RIGHT_2].w = 0000;
    Hunter_Clip[RIGHT_2].h = 0000;

    Hunter_Clip[RIGHT_3].x = 0000;
    Hunter_Clip[RIGHT_3].y = 0000;
    Hunter_Clip[RIGHT_3].w = 0000;
    Hunter_Clip[RIGHT_3].h = 0000;

    //Left
    Hunter_Clip[LEFT_1].x = 0000;
    Hunter_Clip[LEFT_1].y = 0000;
    Hunter_Clip[LEFT_1].w = 0000;
    Hunter_Clip[LEFT_1].h = 0000;

    Hunter_Clip[LEFT_2].x = 0000;
    Hunter_Clip[LEFT_2].y = 0000;
    Hunter_Clip[LEFT_2].w = 0000;
    Hunter_Clip[LEFT_2].h = 0000;

    Hunter_Clip[LEFT_3].x = 0000;
    Hunter_Clip[LEFT_3].y = 0000;
    Hunter_Clip[LEFT_3].w = 0000;
    Hunter_Clip[LEFT_3].h = 0000;
}
