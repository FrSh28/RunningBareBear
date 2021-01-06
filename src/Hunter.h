#ifndef HUNTER_H
#define HUNTER_H
#include <vector>
#include <string>
#include "includeSDL.h"
#include "BasicObject.h"
class Hunter : public BasicObject
{
	SDL_Point HunterPosOnMap;
	SDL_Point HunterPosOnPixel;
	SDL_Point CenterPixel;
	SDL_Point directPos;
	SDL_Point findpos;
	SDL_Point NextPixel;
	int Hvelocity, Run, Walk;
	bool SetSuccess;
	bool Discovered;
	bool arrive;
	bool visible;
	int a;
	int b;
	double deltaX;
	double deltaY;
	double findX;
	double findY;
	std::queue<SDL_Point> go;
	Map *map;
	Runner *runner;

	
public:
	Hunter();
	~Hunter();
	int getHunterPosX_OnMap() const {return HunterPosOnMap.x}
	int getHunterPosY_OnMap() const {return HunterPosOnMap.y}
	void handleEvents(SDL_Event &e);
	void update();
	SDL_Point Set();
	bool RunnerVisible();
	bool Arrive();
	void Stage1();
	void Stage2();
	void Stage3();
	void Chase(SDL_Point, SDL_Point);
	void Move();
};


#endif
