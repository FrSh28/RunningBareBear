#ifndef BUTTOM_H
#define BUTTOM_H
#include "includeSDL.h"
#include "BasicObject.h"

class Buttom : public BasicObject
{
	public:
	static SDL_Rect buttoms[TOTAL_BUTTOMS];
	void handleEvents(SDL_Event &e);
	void update();
	Buttom();
	~Buttom();
	
}

enum buttom
{
	START, STOP, LEAVE, RESUME, SETTING, OK, TOTAL_BUTTOMS
};

#endif
