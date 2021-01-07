#ifndef HUNTER_H
#define HUNTER_H
#include <vector>
#include <string>
#include "includeSDL.h"
#include "BasicObject.h"
class Hunter : public BasicObject
{
	SDL_Point HunterMapPos;
	SDL_Point HunterPixelPos;
	SDL_Point HunterCenterPixel;
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
	int HunterWidth;
	int HunterHeight;
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
	bool handleEvents(SDL_Event &e);
	void update();
	SDL_Point Set();
	SDL_Point getMapPos() {return HunterMapPos;}
	SDL_Point getPixelPos() {return HunterCenterPixel;}
	bool RunnerVisible();
	bool Arrive();
	void Stage1();
	void Stage2();
	void Stage3();
	void Chase(SDL_Point, SDL_Point);
	void Move();
};


#endif
