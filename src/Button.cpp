#include "includeSDL.h"
#include "Game.h"
#include "Button.h"
#include "UserEvent.h"
#include "Layer.h"
#include <cmath>


SDL_Rect Button::buttons[TOTAL_BUTTOMS] = {SDL_Rect({x,y,w,h}), } 

double& operator^(SDL_Point center, SDL_Point mouse)
{
	double ans;
	ans = pow((pow(center.x-mouse.x, 2) + pow(center.y-mouse.y, 2)), 0.5);
	return ans;
	
}

Button::Button(button_type tmp) :
	type(tmp), UpdateReturnType(false)
{
	Center.x = buttons[type].x + buttons[type].w/2;
	Center.y = buttons[type].y + buttons[type].h/2;
	rectOnScreen = buttons[type];
	Inside = false;
}

Button::~Button()
{
	
}

bool Button::handleEvents(SDL_Event &e)
{
	EventReturnType = false;
	int X,Y;
	SDL_GetMouseState( &X, &Y );
	SDL_Point mouse;
	mouse.x = X;
	mouse.y = Y;
	switch(type)
	{
		case START://
			if(e.type == SDL_MOUSEMOTION)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[START].w/2 )
				{
					Inside = true;
				}
				if(Last != Inside)
					UpdateReturnType = true;
				else
					UpdateReturnType = false;
			}
			else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				if(Inside)
					createUserEvent(GAMESTATE_CHANGE, START, NULL, NULL); 
			}
			break;
		case INTRO1://
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[INTRO1].w/2 )
				{
					Inside = true;
				}
				if(Inside)
				{
					createUserEvent(GAMESTATE_CHANGE, PAUSE, NULL, NULL);
					Game &game = Game::GetGame();
					game.pushOverlayer(new boardLayer("Intro", INTRO_IMAGE));
					
				}
			}
			break;
		case LEAVEINTRO1://
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[LEAVEINTRO1].w/2 )
				{
					Inside = true;
				}
				if(Inside)
				{
					createUserEvent(GAMESTATE_CHANGE, RESUME, NULL, NULL);
					Game &game = Game::GetGame();
					game.popTopOverlayer();
				}
			}
			break;
		case MISSION://
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[INTRO1].w/2 )
				{
					Inside = true;
				}
				if(Inside)
				{
					createUserEvent(GAMESTATE_CHANGE, PAUSE, NULL, NULL);
					Game &game = Game::GetGame();
					if(curMission == Mission1Type1)
						game.pushOverlayer(new boardLayer("M1-1", MISSION_1_1_IMAGE));
						
					else if(curMission == Mission1Type2)
						game.pushOverlayer(new boardLayer("M1-2", MISSION_1_2_IMAGE));
						
					else if(curMission == Mission1Type3)
						game.pushOverlayer(new boardLayer("M1-3", MISSION_1_3_IMAGE));
						
					else if(curMission == Mission2Type1)
						game.pushOverlayer(new boardLayer("M2-1", MISSION_2_1_IMAGE));
						
					else if(curMission == Mission2Type2)
						game.pushOverlayer(new boardLayer("M2-2", MISSION_2_2_IMAGE));
						
					else if(curMission == Mission2Type3)
						game.pushOverlayer(new boardLayer("M2-3", MISSION_2_3_IMAGE));
					//Layer
				}
			}
			break;
		case LEAVEMISSION://
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[LEAVEMISSION].w/2 )
				{
					Inside = true;
				}
				if(Inside)
				{
					createUserEvent(GAMESTATE_CHANGE, RESUME, NULL, NULL);
					Game &game = Game::GetGame();
					game.popTopOverlayer();
				}
			}
			break;
		case PAUSES://
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[PAUSE].w/2 )
				{
					Inside = true;
				}
				if(Inside)
				{
					Game &game = Game::GetGame();
					game.pushOverlayer(new pauseLayer);
					
					//some user event
				}
			}
			break;
		case LEAVE:
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[LEAVE].w/2 )
				{
					Inside = true;
				}
				if(Inside)
				{
					createUserEvent(GAMESTATE_CHANGE, STARTMENU, NULL, NULL);
				}
			}
			break;
		case RESUMES://
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[RESUMES].w/2 )
				{
					Inside = true;
				}
				if(Inside)
				{
					createUserEvent(GAMESTATE_CHANGE, RESUME, NULL, NULL);
					Game &game = Game::GetGame();
					game.popTopOverlayer();
				}
			}
			break;
		case INTRO2://
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[INTRO2].w/2 )
				{
					Inside = true;
				}
				if(Inside)
				{
					createUserEvent(GAMESTATE_CHANGE, PAUSE, NULL, NULL);
					Game &game = Game::GetGame();
					game.pushOverlayer(new boardLayer("Intro", INTRO_IMAGE));
				}
			}
			break;
		case LEAVEINTRO2://
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[LEAVEINTRO2].w/2 )
				{
					Inside = true;
				}
				if(Inside)
				{
					createUserEvent(GAMESTATE_CHANGE, RESUME, NULL, NULL);
					Game &game = Game::GetGame();
					game.popTopOverlayer();
				}
			}
			break;
		case OK:
			if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				EventReturnType = true;
				Inside = false;
				if((Center ^ mouse) <= buttons[OK].w/2 )
				{
					Inside = true;
				}
				if(Inside)
				{
					createUserEvent(GAMESTATE_CHANGE, STARTMENU, NULL, NULL);
				}
			}
			break;
	}
	return EventReturnType;
}

bool Button::update()
{
	if(type == START && Inside)
		rectOnTexture = SDL_Rect( {button_type[START].x+button_type[START].w, button_type[START].y, button_type[START].w, button_type[START].h} );
	else
		rectOnTexture = SDL_Rect( {button_type[type].x, button_type[type].y, button_type[type].w, button_type[type].h} );
	Last = Inside;
	return UpdateReturnType;
/*
	switch(type)
	{
		case START:
			if(Inside) 
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
		case INTRO1:
			rectOnTexture = SDL_Rect( {button_type[INTRO1].x, button_type[INTRO1].y, button_type[INTRO1].w, button_type[INTRO1].h} );
			break;
		case LEAVEINTRO1:
			rectOnTexture = SDL_Rect( {button_type[LEAVEINTRO1].x, button_type[LEAVEINTRO1].y, button_type[LEAVEINTRO1].w, button_type[LEAVEINTRO1].h} );
			break;
		case RESUMES:
			rectOnTexture = SDL_Rect( {button_type[RESUMES].x, button_type[RESUMES].y, button_type[RESUMES].w, button_type[RESUMES].h} );
			break;
		case INTRO2:
			rectOnTexture = SDL_Rect( {button_type[INTRO2].x, button_type[INTRO2].y, button_type[INTRO2].w, button_type[INTRO2].h} );
			break;
		case LEAVEINTRO2:
			rectOnTexture = SDL_Rect( {button_type[LEAVEINTRO2].x, button_type[LEAVEINTRO2].y, button_type[LEAVEINTRO2].w, button_type[LEAVEINTRO2].h} );
			break;
		case OK:
			rectOnTexture = SDL_Rect( {button_type[OK].x, button_type[OK].y, button_type[OK].w, button_type[OK].h} );
			break;
	}
*/
}

