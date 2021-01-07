#ifndef BUTTON_H
#define BUTTON_H
#include "includeSDL.h"
#include "BasicObject.h"
enum button_type
{
	START, PAUSE, LEAVE, RESUME, SETTING, LEAVESETTING, OK, TOTAL_BUTTOMS
};

class Button : public BasicObject
{
	bool InsideStart;
	bool InsidePause;
	bool InsideLeave;
	bool InsideResume;
	bool InsideSetting;
	bool InsideLeaveSetting;
	bool InsideOk;
	button_type type;
	public:
	static SDL_Rect buttons[TOTAL_BUTTOMS];
	bool handleEvents(SDL_Event &e);
	void update();
	Button(button_type tmp);
	~Button();
	
}



#endif // BUTTON_H
