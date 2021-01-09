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
	SDL_Point StartCenter;
	SDL_Point PauseCenter;
	SDL_Point LeaveCenter;
	SDL_Point ResumeCenter;
	SDL_Point SettingCenter;
	SDL_Point LeaveSettingCenter;
	SDL_Point OkCenter;
	button_type type;
public:
	static SDL_Rect buttons[TOTAL_BUTTOMS];
	bool handleEvents(SDL_Event &e);
	bool update();
	Button(button_type tmp);
	~Button();
	
}

SDL_Point& operator ^(SDL_Point, SDL_Point);

#endif // BUTTON_H
