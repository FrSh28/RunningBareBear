#include "includeSDL.h"
#include "Game.h"
#include "Button.h"
#include <cmath>
/*
Button::buttons[START] = {x,y,w,h};
Button::buttons[STOP]
Button::buttons[LEAVE]
Button::buttons[RESUME]
Button::buttons[SETTING]
Button::buttons[OK]
*/
SDL_Rect Button::buttons[TOTAL_BUTTOMS] = {SDL_Rect({x,y,w,h}), } 

Button::Button()
{
	
}

Button::~Button()
{
	
}

void Button::handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEMOTION)
	{
		int X,Y;
		SDL_GetMouseState( &X, &Y );
		if() //at start page(initial)
		{
			InsideStart = true;
			SDL_Point StartCenter;
			StartCenter.x = buttons[START].x + buttons[START].w/2;
			StartCenter.y = buttons[START].y + buttons[START].h/2;
			if(pow((X-StartCenter.x), 2) + pow((Y-StartCenter.y), 2) > pow(buttons[START].w/2, 2) )
			{
				InsideStart = false;
			}
			if(InsideStart) //render start2
			else //render start1
		}
		else if() //at playing page
		{
			InsidePause = true;
			if(x < buttons[PAUSE].x || x > (buttons[PAUSE].x + buttons[PAUSE].w) || 
			   y < buttons[PAUSE].y || y > (buttons[PAUSE].y + buttons[PAUSE].h))
			{
				InsidePause = false;
			}
			//render pause button
		}
		else if() //at pause page 
		{
			InsideLeave = true;
			InsideResume = true;
			InsideSetting = true;
			if()
			{
				InsideLeave = false;
			}
			if()
			{
				InsideResume = false;
			}
			if()
			{
				InsideSetting = false;
			}
		}
		else if() //at setting page  
		{
			InsideLeaveSetting = true;
			if()
			{
				InsideLeaveSetting = false;
			}
		}
		else //at end page
		{
			InsideOk = true;
			if()
			{
				InsideOk - false;
			}
		}
		
	}
	if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		if() //at start page && InsideStart
		{
			//at start page = false
			//at playing page = true
		}
		else if() //at playing page && InsidePause
		{
			//at playing page = false
			//at puase page = true
		}
		else if() //at pause page && InsideLeave
		{
			//at pause page = false
			//at start page = true
		}
		else if() //at pause page && InsideResume
		{
			//at pause page = false  
			//at playing page = true
		}
		else if() //at pause page && InsideSetting
		{
			//at pause page = false
			//at setting page = true
		}
		else if() //at setting page && InsideColseSetting
		{
			//at setting page = false
			//at pause page = true
		}
		else if() //at end page && InsideOk
		{
			//at end page = false
			//at start page = true
		}
	}
}

void Button::update()
{
	if() //game ends
	{
		//set every page into false
		//set end page into true
	}
}

