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

SDL_Point& operator^(SDL_Point center, SDL_Point mouse)
{
	double ans;
	ans = pow((pow(center.x-mouse.x, 2) + pow(center.y-mouse.y, 2)), 0.5);
	return ans;
	
}

Button::Button(button_type tmp) :
	type(tmp)
{
	StartCenter.x = buttons[START].x + buttons[START].w/2;
	StartCenter.y = buttons[START].y + buttons[START].h/2;
	
	PauseCenter.x = buttons[PAUSE].x + buttons[PAUSE].w/2;
	PauseCenter.y = buttons[PAUSE].y + buttons[PAUSE].h/2;
	
	LeaveCenter.x = buttons[LEAVE].x + buttons[LEAVE].w/2;
	LeaveCenter.y = buttons[LEAVE].y + buttons[LEAVE].h/2;
	
	ResumeCenter.x = buttons[RESUME].x + buttons[RESUME].w/2;
	ResumeCenter.y = buttons[RESUME].y + buttons[RESUME].h/2;
	
	SettingCenter.x = buttons[SETTING].x + buttons[SETTING].w/2;
	SettingCenter.y = buttons[SETTING].y + buttons[SETTING].h/2;
	
	LeaveSettingCenter.x = buttons[LEAVESETTING].x + buttons[LEAVESETTING].w/2;
	LeaveSettingCenter.y = buttons[LEAVESETTING].y + buttons[LEAVESETTING].h/2;
	
	OKCenter.x = buttons[OK].x + buttons[OK].w/2;
	OKCenter.y = buttons[OK].y + buttons[OK].h/2;
	
}

Button::~Button()
{
	
}

bool Button::handleEvents(SDL_Event &e)
{
	int X,Y;
	SDL_GetMouseState( &X, &Y );
	SDL_Point mouse;
	mouse.x = X;
	mouse.y = Y;
	switch(type)
	{
		case START:
			if(e.type == SDL_MOUSEMOTION)
			{
				InsideStart = false;			
				if((StartCenter ^ mouse) <= buttons[START].w/2 )
				{
					InsideStart = true ;
				}
			}
			else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && InsideStart)
			{
				//some user event
			}
			break;
		case PAUSE:
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				InsidePause = false;
				if((PauseCenter ^ mouse) <= buttons[PAUSE].w/2 )
				{
					InsidePause = true;
				}
				if(InsidePause)
				{
					//some user event
				}
			}
			break;
		case LEAVE:
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				InsideLeave = false;
				if((LeaveCenter ^ mouse) <= buttons[LEASE].w/2 )
				{
					InsideLease = true;
				}
				if(InsideLave)
				{
					//some user event
				}
			}
			break;
		case RESUME:
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				InsideResume = false;
				if((ResumeCenter ^ mouse) <= buttons[RESUME].w/2 )
				{
					InsideResume = true;
				}
				if(InsideResume)
				{
					//some user event
				}
			}
			break;
		case SETTING:
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				InsideSetting = false;
				if((SettingCenter ^ mouse) <= buttons[SETTING].w/2 )
				{
					InsideSetting = true;
				}
				if(InsideSetting)
				{
					//some user event
				}
			}
			break;
		case LEAVESETTING:
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				InsideLeaveSetting = false;
				if((LeaveSettingCenter ^ mouse) <= buttons[LEAVESETTING].w/2 )
				{
					InsideLeaveSetting = true;
				}
				if(InsideLeaveSetting)
				{
					//some user event
				}
			}
			break;
		case OK:
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				InsideOk = false;
				if((OkCenter ^ mouse) <= buttons[OK].w/2 )
				{
					InsideOk = true;
				}
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

