#include "includeSDL.h"
#include "Game.h"
#include "Buttom.h"
#include<cmath>
/*
Buttom::buttoms[START] = {x,y,w,h};
Buttom::buttoms[PAUSE]
Buttom::buttoms[LEAVE]
Buttom::buttoms[RESUME]
Buttom::buttoms[SETTING]
Buttom::buttoms[OK]
*/
SDL_Rect Buttom::buttoms[TOTAL_BUTTOMS] = {SDL_Rect({x,y,w,h}), } 

Buttom::Buttom()
{
	
}

Buttom::~Buttom()
{
	
}

void Buttom::handleEvents(SDL_Event &e)
{
	if(e.type == SDL_MOUSEMOTION)
	{
		int X,Y;
		SDL_GetMouseState( &X, &Y );
		if() //at start page(initial)
		{
			InsideStart = true;
			SDL_Point StartCenter;
			StartCenter.x = buttoms[START].x + buttoms[START].w/2;
			StartCenter.y = buttoms[START].y + buttoms[START].h/2;
			if(pow((X-StartCenter.x), 2) + pow((Y-StartCenter.y), 2) > pow(buttoms[START].w/2, 2) )
			{
				InsideStart = false;
			}
			if(InsideStart) //render start2
			else //render start1
		}
		else if() //at playing page
		{
			InsidePause = true;
			if(x < buttoms[PAUSE].x || x > (buttoms[PAUSE].x + buttoms[PAUSE].w) || 
			   y < buttoms[PAUSE].y || y > (buttoms[PAUSE].y + buttoms[PAUSE].h))
			{
				InsidePause = false;
			}
			//render pause buttom
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

void Buttom::update()
{
	if() //game ends
	{
		//set every page into false
		//set end page into true
	}
}

