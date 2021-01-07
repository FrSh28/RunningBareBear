#ifndef BUTTON_H
#define BUTTON_H
#include "includeSDL.h"
#include "BasicObject.h"

class Button : public BasicObject
{
	bool InsideStart;
	bool InsidePause;
	bool InsideLeave;
	bool InsideResume;
	bool InsideSetting;
	bool InsideLeaveSetting;
	bool InsideOk;
	public:
	static SDL_Rect buttons[TOTAL_BUTTOMS];
	void handleEvents(SDL_Event &e);
	void update();
	Button();
	~Button();
	
}

enum button
{
	START, PAUSE, LEAVE, RESUME, SETTING, LEAVESETTING, OK, TOTAL_BUTTOMS
};

#endif // BUTTON_H
