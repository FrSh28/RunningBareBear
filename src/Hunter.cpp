#include "includeSDL.h"
#include "Game.h"
#include "Hunter.h"
#include "Map.h"
#include "UserEvent.h"
#include "Character.h"
#include <queue>
#include <iostream>
#include <cmath>
using namespace std;

SDL_Rect Hunter_Clip[TOTAL];

Character *createHunter(SDL_Point _mapPos, SDL_Point _pixelPos)
{
	return new Hunter(_mapPos, _pixelPos);
}

Hunter::Hunter(SDL_Point MapPos, SDL_Point PixelPos) :
	Hvelocity(0), arrive(false), SetSuccess(false), Discovered(false),
	Animation_Frame(4), Run(8), Walk(5), updateRate(30), frame(0), map(&Map::getMap())//SPEED
{
	direction = DOWN_1;
	texture = loadImage(HUNTER_IMAGE);
	rectOnTexture = Hunter_Clip[direction+frame/updateRate];
	initHunter_Clips();
	setMapPos(MapPos);
	setPixelPos(PixelPos);
	directPos = HunterPixelPos;
	rectOnScreen.w = Map::getPixelWidth();
	rectOnScreen.h = Map::getPixelHeight();
}

void Hunter::setMapPos(SDL_Point &MapPos)
{
	HunterMapPos = MapPos;
}

void Hunter::setPixelPos(SDL_Point &PixelPos)
{
	HunterCenterPixel = PixelPos;
	HunterPixelPos.x = HunterCenterPixel.x - rectOnScreen.w/2;
	HunterPixelPos.y = HunterCenterPixel.y - rectOnScreen.h/2;
	rectOnScreen.x = HunterPixelPos.x;
	rectOnScreen.y = HunterPixelPos.y;
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
	HunterCenterPixel.x = HunterPixelPos.x + rectOnScreen.w/2;
	HunterCenterPixel.y = HunterPixelPos.y + rectOnScreen.h/2;
	HunterMapPos = map->pixelPosTomapPos(HunterCenterPixel);
	RunnerMapPos = map->getRunnerMapPos();
	
	Stage3();
		
	rectOnTexture = Hunter_Clip[direction+frame/updateRate];
	frame ++;
	if(frame/updateRate == Animation_Frame){frame=0;}
	//if it change return true
	/*if(HunterPixelPos.x < 0 || HunterPixelPos.y < 0)
	{
		Game &game = Game::GetGame();
		HunterPixelPos.x = game.rdEngine() % 1400;
		HunterPixelPos.y = game.rdEngine() % 1400;
		HunterCenterPixel.x = HunterPixelPos.x + rectOnScreen.w/2;
		HunterCenterPixel.y = HunterPixelPos.y + rectOnScreen.h/2;
		HunterMapPos = map->pixelPosTomapPos(HunterCenterPixel);
	}*/
	rectOnScreen.x = HunterPixelPos.x;
	rectOnScreen.y = HunterPixelPos.y;
	return true;
}

bool Hunter::RunnerVisible()
{
	double a, b, deltaX, deltaY, findX, findY;
	SDL_Point findpos;
	visible = true;
	a = RunnerMapPos.x - HunterMapPos.x;
	b = RunnerMapPos.y - HunterMapPos.y;
	deltaX = a / sqrt(a*a+b*b);
	deltaY = b / sqrt(a*a+b*b);
	findpos = HunterMapPos;
	findX = HunterMapPos.x;
	findY = HunterMapPos.y;
	while(findpos.x != RunnerMapPos.x || findpos.y != RunnerMapPos.y)
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
	updateRate = 30;
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
	updateRate = 30;
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
	updateRate = 60;
	if(Arrive(directPos))
	{
		SDL_Point SetPos;
		Game &game = Game::GetGame();
		SetPos.x = abs((HunterMapPos.x + int(game.rdEngine()%20) - 10) % 30);
		directPos.x = SetPos.x;
		SetPos.y = abs((HunterMapPos.y + int(game.rdEngine()%20) - 10) % 30);
		directPos.y = SetPos.y;
		Chase(HunterMapPos, directPos);
		NextPixel = map->mapPosTopixelPos(HunterMapPos);
	}
	Move();
}

bool Hunter::Arrive(SDL_Point destination)
{
	arrive = false;
	if(abs(HunterPixelPos.x - destination.x) < Hvelocity && abs(HunterPixelPos.y - destination.y) < Hvelocity)
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
		go.pop();
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
		SetPos.x = (HunterMapPos.x + game.rdEngine()%20 - 5) % 30;
		SetPos.y = (HunterMapPos.y + game.rdEngine()%20 - 5) % 30;
		if(map->isSpace(SetPos)) 
		{
			SetSuccess = true;
			return SetPos;
		} 
	}
}

void Hunter::Chase(SDL_Point HunterMapPos, SDL_Point directpos)
{
	if(directpos.x == 0) printf("aaa");
	if(directpos.y == 0) printf("ada");
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
		Node(const Node &x){
			step = x.step;
			for(auto it = x.way.begin(); it != x.way.end(); ++it)
			{
				way.push_back(*it);
			}
		}
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
			//printf("aaa");
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
			//printf("bbb\n");
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
			//printf("ccc\n");
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
			//printf("ddd\n");
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
    Hunter_Clip[UP_1].x = 32;
    Hunter_Clip[UP_1].y = 96;
    Hunter_Clip[UP_1].w = 32;
    Hunter_Clip[UP_1].h = 32;

    Hunter_Clip[UP_2].x = 00;
    Hunter_Clip[UP_2].y = 96;
    Hunter_Clip[UP_2].w = 32;
    Hunter_Clip[UP_2].h = 32;

    Hunter_Clip[UP_3].x = 32;
    Hunter_Clip[UP_3].y = 96;
    Hunter_Clip[UP_3].w = 32;
    Hunter_Clip[UP_3].h = 32;
    
    Hunter_Clip[UP_4].x = 64;
    Hunter_Clip[UP_4].y = 96;
    Hunter_Clip[UP_4].w = 32;
    Hunter_Clip[UP_4].h = 32;

    // Down
    Hunter_Clip[DOWN_1].x = 32;
    Hunter_Clip[DOWN_1].y = 00;
    Hunter_Clip[DOWN_1].w = 32;
    Hunter_Clip[DOWN_1].h = 32;

    Hunter_Clip[DOWN_2].x = 00;
    Hunter_Clip[DOWN_2].y = 00;
    Hunter_Clip[DOWN_2].w = 32;
    Hunter_Clip[DOWN_2].h = 32;

    Hunter_Clip[DOWN_3].x = 32;
    Hunter_Clip[DOWN_3].y = 00;
    Hunter_Clip[DOWN_3].w = 32;
    Hunter_Clip[DOWN_3].h = 32;
    
    Hunter_Clip[DOWN_4].x = 64;
    Hunter_Clip[DOWN_4].y = 00;
    Hunter_Clip[DOWN_4].w = 32;
    Hunter_Clip[DOWN_4].h = 32;

    //Right
    Hunter_Clip[RIGHT_1].x = 32;
    Hunter_Clip[RIGHT_1].y = 64;
    Hunter_Clip[RIGHT_1].w = 32;
    Hunter_Clip[RIGHT_1].h = 32;

    Hunter_Clip[RIGHT_2].x = 00;
    Hunter_Clip[RIGHT_2].y = 64;
    Hunter_Clip[RIGHT_2].w = 32;
    Hunter_Clip[RIGHT_2].h = 32;

    Hunter_Clip[RIGHT_3].x = 32;
    Hunter_Clip[RIGHT_3].y = 64;
    Hunter_Clip[RIGHT_3].w = 32;
    Hunter_Clip[RIGHT_3].h = 32;
    
    Hunter_Clip[RIGHT_4].x = 64;
    Hunter_Clip[RIGHT_4].y = 64;
    Hunter_Clip[RIGHT_4].w = 32;
    Hunter_Clip[RIGHT_4].h = 32;

    //Left
    Hunter_Clip[LEFT_1].x = 32;
    Hunter_Clip[LEFT_1].y = 32;
    Hunter_Clip[LEFT_1].w = 32;
    Hunter_Clip[LEFT_1].h = 32;

    Hunter_Clip[LEFT_2].x = 00;
    Hunter_Clip[LEFT_2].y = 32;
    Hunter_Clip[LEFT_2].w = 32;
    Hunter_Clip[LEFT_2].h = 32;

    Hunter_Clip[LEFT_3].x = 32;
    Hunter_Clip[LEFT_3].y = 32;
    Hunter_Clip[LEFT_3].w = 32;
    Hunter_Clip[LEFT_3].h = 32;
    
    Hunter_Clip[LEFT_4].x = 64;
    Hunter_Clip[LEFT_4].y = 32;
    Hunter_Clip[LEFT_4].w = 32;
    Hunter_Clip[LEFT_4].h = 32;
}
