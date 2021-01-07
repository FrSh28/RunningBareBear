#ifndef BUTTOM_H
#define BUTTOM_H
#include "includeSDL.h"
#include "BasicObject.h"

class Buttom : public BasicObject
{
	bool InsideStart;
	bool InsidePause;
	bool InsideLeave;
	bool InsideResume;
	bool InsideSetting;
	bool InsideLeaveSetting;
	bool InsideOk;
	public:
	static SDL_Rect buttoms[TOTAL_BUTTOMS];
	void handleEvents(SDL_Event &e);
	void update();
	Buttom();
	~Buttom();
	
}

enum buttom
{
	START, PAUSE, LEAVE, RESUME, SETTING, LEAVESETTING, OK, TOTAL_BUTTOMS
};

#endif
