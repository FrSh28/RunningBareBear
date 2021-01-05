#ifndef HUNTER_H
#define HUNTER_H
#include <vector>
#include <string>
#include "includeSDL.h"
#include "Renderable.h"
class Hunter : public Renderable
{
	SDL_Point HunterPosOnMap;
	SDL_Point directPos;
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
	
	
public:
	Hunter();
	~Hunter();
	int getHunterPosX_OnMap() const {return HunterPosOnMap.x}
	int getHunterPosY_OnMap() const {return HunterPosOnMap.y}
	
	bool handleEvents(SDL_Event &e);
	void update();
	bool RunnerVisible();
	bool Arrive();
	void Stage1();
	void Stage2();
	void Stage3();
	void Chase(SDL_Point, SDL_Point);
};


#endif
