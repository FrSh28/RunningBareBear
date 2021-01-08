#include "includeSDL.h"
#include "Game.h"
#include "Button.h"
#include <cmath>
/*
	START, PAUSE, LEAVE, RESUME, SETTING, LEAVESETTING, OK, TOTAL_BUTTOMS
Button::buttons[START] = {x,y,w,h};
Button::buttons[STOP]
Button::buttons[LEAVE]
Button::buttons[RESUME]
Button::buttons[SETTING]
Button::buttons[OK]
*/
SDL_Rect Button::button_type[TOTAL_BUTTOMS] = {SDL_Rect({x,y,w,h}), } 

Button::Button(button_type tmp) :
	type(tmp)
{
	
}

Button::~Button()
{
	
}
bool Button::handleEvents(SDL_Event &e)
{
	int X,Y;
	SDL_GetMouseState( &X, &Y );
	switch(type)
	{
		case START:
			if(e.type == SDL_MOUSEMOTION)
			{
				
				InsideStart = false;
				SDL_Point StartCenter;
				StartCenter.x = buttons[START].x + buttons[START].w/2;
				StartCenter.y = buttons[START].y + buttons[START].h/2;
				if((pow( (X-StartCenter.x), 2) + pow((Y-StartCenter.y), 2) ) <= pow(buttons[START].w/2, 2) )
				{
					InsideStart =true ;
				}
				if(InsideStart) 
					rectOnTexture = SDL_Rect( {button_type[START].x+button_type[START].w, button_type[START].y, button_type[START].w, button_type[START].h} );
				else 
					rectOnTexture = SDL_Rect( {button_type[START].x, button_type[START].y, button_type[START].w, button_type[START].h} );
			}
			else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && InsideStart)
			{
				//some user event
			}
			break;
		case PAUSE:
			rectOnTexture = SDL_Rect( {button_type[PAUSE].x, button_type[PAUSE].y, button_type[PAUSE].w, button_type[PAUSE].h} );
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				//determine whether it is inside pause
				if(InsidePause)
				{
					//some user event
				}
			}
			break;
		case LEAVE:
			rectOnTexture = SDL_Rect( {button_type[LEAVE].x, button_type[LEAVE].y, button_type[LEAVE].w, button_type[LEAVE].h} );
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				//determine whether it is inside LEAVE
				if(InsideLave)
				{
					//some user event
				}
			}
			break;
		case RESUME:
			rectOnTexture = SDL_Rect( {button_type[RESUME].x, button_type[RESUME].y, button_type[RESUME].w, button_type[RESUME].h} );
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				//determine whether it is inside RESUME
				if(InsideResume)
				{
					//some user event
				}
			}
			break;
		case SETTING:
			rectOnTexture = SDL_Rect( {button_type[SETTING].x, button_type[SETTING].y, button_type[SETTING].w, button_type[SETTING].h} );
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				//determine whether it is inside SETTING
				if(InsideSetting)
				{
					//some user event
				}
			}
			break;
		case LEAVESETTING:
			rectOnTexture = SDL_Rect( {button_type[LEAVESETTING].x, button_type[LEAVESETTING].y, button_type[LEAVESETTING].w, button_type[LEAVESETTING].h} );
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				//determine whether it is inside LEAVESETTING
				if(InsideLeaveSetting)
				{
					//some user event
				}
			}
			break;
		case OK:
			rectOnTexture = SDL_Rect( {button_type[OK].x, button_type[OK].y, button_type[OK].w, button_type[OK].h} );
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				//determine whether it is inside OK
				if(InsideOk)
				{
					//some user event
				}
			}
			break;
	}
}

bool Button::update()
{
	switch(type)
	{
		case START:
			if(InsideStart) 
				rectOnTexture = SDL_Rect( {button_type[START].x+button_type[START].w, button_type[START].y, button_type[START].w, button_type[START].h} );
			else 
				rectOnTexture = SDL_Rect( {button_type[START].x, button_type[START].y, button_type[START].w, button_type[START].h} );
		}
		break;
		case PAUSE:
			rectOnTexture = SDL_Rect( {button_type[PAUSE].x, button_type[PAUSE].y, button_type[PAUSE].w, button_type[PAUSE].h} );
			break;
		case LEAVE:
			rectOnTexture = SDL_Rect( {button_type[LEAVE].x, button_type[LEAVE].y, button_type[LEAVE].w, button_type[LEAVE].h} );
			break;
		case RESUME:
			rectOnTexture = SDL_Rect( {button_type[RESUME].x, button_type[RESUME].y, button_type[RESUME].w, button_type[RESUME].h} );
			break;
		case SETTING:
			rectOnTexture = SDL_Rect( {button_type[SETTING].x, button_type[SETTING].y, button_type[SETTING].w, button_type[SETTING].h} );
			break;
		case LEAVESETTING:
			rectOnTexture = SDL_Rect( {button_type[LEAVESETTING].x, button_type[LEAVESETTING].y, button_type[LEAVESETTING].w, button_type[LEAVESETTING].h} );
			break;
		case OK:
			rectOnTexture = SDL_Rect( {button_type[OK].x, button_type[OK].y, button_type[OK].w, button_type[OK].h} );
			break;
	}
}

