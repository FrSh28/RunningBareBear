#ifndef HUNTER_H
#define HUNTER_H
#include <vector>
#include <string>
#include "includeSDL.h"
#include "BasicObject.h"
class Hunter : public BasicObject
{
	SDL_Point HunterMapPos;
	SDL_Point RunnerMapPos; 
	SDL_Point HunterPixelPos;
	SDL_Point HunterCenterPixel;
	SDL_Point directPos;
	SDL_Point findpos;
	SDL_Point NextPixel;
	int Hvelocity
	const int Run;
	const int Walk;
	bool SetSuccess;
	bool Discovered;
	bool arrive;
	bool visible;
	int a;
	int b;
	int HunterWidth;
	int HunterHeight;
	int updateRate;
	int Animation_Frames;
	double deltaX;
	double deltaY;
	double findX;
	double findY;
	std::queue<SDL_Point> go;
	frames direction;
	Map *map;
	Runner *runner;
	
	
public:
	Hunter(SDL_Point, SDL_Point);
	~Hunter();
	bool handleEvents(SDL_Event &e);
	bool update();
	SDL_Point Set();
	SDL_Point getMapPos() {return HunterMapPos;}
	SDL_Point getPixelPos() {return HunterCenterPixel;}
	bool RunnerVisible();
	bool Arrive();
	void setPixelPos(SDL_Point &);
	void setMapPos(SDL_Point &);
	void Stage1();
	void Stage2();
	void Stage3();
	void Chase(SDL_Point, SDL_Point);
	void Move();
	void initHunter_Clips();
};
enum frames
{
	UP_1, UP_2, UP_3, DOWN_1, DOWN_2, DOWN_3, RIGHT_1, RIGHT_2, RIGHT_3, LEFT_1, LEFT_2, LEFT_3, TOTAL
}

#endif
