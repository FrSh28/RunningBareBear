#ifndef HUNTER_H
#define HUNTER_H
#include <vector>
#include <string>
#include "includeSDL.h"
#include "Renderable.h"
class Hunter : public Renderable
{
	SDL_Point HunterPosOnMap;
	int HunterSpeed;
	int HunterRun;
	int HunterWalk;
	bool SetSuccess;
	bool Discovered;
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
};

/*
Hunter::Hunter()
{
	posOnWindow = NULL;
	pos
}

Hunter::~Hunter()
{
	
}

void Hunter::handleEvents(SDL_Event &e)
{
	
}

void Hunter::update()
{
	posOnWindow = Map::convertPos(pos);
}
*/
#endif
