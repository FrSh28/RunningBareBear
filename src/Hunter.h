#ifndef HUNTER_H
#define HUNTER_H
#include <vector>
#include <string>
#include "includeSDL.h"
#include "Renderable.h"
class Hunter : public Renderable
{
	SDL_Point HunterPosOnMap;
	int Hvelocity, Run, Walk;
	bool SetSuccess;
	bool Discovered;
	bool gameover;
	bool visible;
	double deltaX, deltaY;
	double a, b;
	double up_d, down_d, right_d, left_d;
	double minimum;
	int findX, findY;
	int rememberX, rememberY;
	SDL_Point up, down, right, left;
	
	
public:
	Hunter();
	~Hunter();
	int getHunterPosX_OnMap() const {return HunterPosOnMap.x}
	int getHunterPosY_OnMap() const {return HunterPosOnMap.y}
	
	bool handleEvents(SDL_Event &e);
	void update();
	bool RunnerVisible();
	bool GameOver();
	void Stage1();
	void Stage2();
	void Stage3();
	void Chase();
};


#endif
