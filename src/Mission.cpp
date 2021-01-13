#include <iostream>
#include <string>
#include "includeSDL.h"
#include "Game.h"
#include "Layer.h"
#include "Mission.h"
#include "UserEvent.h"
#include "Item.h"
#include "Map.h" 
using namespace std;

MissionTypes Mission::curMission = MissionTotal;

Mission :: Mission(string _name)
{
	total = 0;
	success = false;
	//posOnWindow->x = ;
	//posOnWindow->y = ;
	//posOnWindow->w = ;
	//posOnWindow->h = ;
	//posOnTexture->x = ;
	//posOnTexture->y = ;
	//posOnTexture->w = ;
	//posOnTexture->h = ;
}
Mission :: ~Mission() //call when mission is complete or timeover ,Current_Mission = 0
{ }

Mission *createMission(MissionTypes choice)
{
	
	switch (choice) //somewhere : srand(time(0)); CreateMission(rand()%MissionTotal);
	{
		case Mission1Type1:
			return new Mission1_1();
		case Mission1Type2:
			return new Mission1_2();
		case Mission1Type3:
			return new Mission1_3();
		/*
		case Mission2Type2:
			return new Mission2_2();
		*/
		case Mission2Type1:
			return new Mission2_1();
		case Mission2Type3:
			return new Mission2_3();			

	}
}
void Mission::timeup()
{
	if(!success)
	{
		Map &map = Map::getMap();
		map.addHunter(3-total); 
	}
}
Mission1_1 :: Mission1_1 ()
 : Mission("Mission 1 ")
{
	curMission = Mission1Type1;
	Map &map = Map::getMap();	
	bool SetSuccess = false;
	SDL_Point SetPos;
	while(!SetSuccess)
	{
		Game &game = Game::GetGame();
		SetPos.x = game.rdEngine()%(map.getRowNum()); 
		SetPos.y = game.rdEngine()%(map.getColNum());
		if(map.isSpace(SetPos)) 
		{
			SetSuccess = true;
		} 
	}
	Sheet* sheet;
	sheet = new Sheet;

	map.placeItem(SetPos, sheet);

}
Mission1_1 :: ~Mission1_1 ()
{
	if(!success)
	{
		//timer + time
	}
}
bool Mission1_1 :: handleEvents(SDL_Event &e)
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == SHEET)
			{
				success = true;
				return true;
			}
		}
	else return false;
}
bool Mission1_1 :: update()
{
	 return false;
}


Mission1_2 :: Mission1_2 ()
 : Mission("Mission 1 ")
{
	curMission = Mission1Type2;
	Map &map = Map::getMap();
	
	bool SetSuccess = false;
	SDL_Point SetPos;
	while(!SetSuccess)
	{
		Game &game = Game::GetGame();
		SetPos.x = game.rdEngine()%(map.getRowNum()); 
		SetPos.y = game.rdEngine()%(map.getColNum());
		if(map.isSpace(SetPos)) 
		{
			SetSuccess = true;
		} 
	}
	Library* lib;
	lib = new Library;
	map.placeItem(SetPos, lib);

}

Mission1_2 :: ~Mission1_2 ()
{
	
}

bool Mission1_2 :: handleEvents(SDL_Event &e)
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == LIBRARY)
			{
				success = true;
				return true;
			}
		}
	return false;
}

bool Mission1_2 :: update()
{
	 return false;
}

Mission1_3 :: Mission1_3 ()
 : Mission("Mission 1 ")
{
	curMission = Mission1Type3;
	Map &map = Map::getMap();
	
	bool SetSuccess = false;
	SDL_Point SetPos;
	while(!SetSuccess)
	{
		Game &game = Game::GetGame();
		SetPos.x = game.rdEngine()%(map.getRowNum()); 
		SetPos.y = game.rdEngine()%(map.getColNum());
		if(map.isSpace(SetPos)) 
		{
			SetSuccess = true;
		} 
	}
	//PE_Teacher
	PE_Teacher* pe;
	pe = new PE_Teacher;
	map.placeItem(SetPos, pe);

}

Mission1_3 :: ~Mission1_3 ()
{
	if(!success)
	{
		// 
	}
}

bool Mission1_3 :: handleEvents(SDL_Event &e)
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == PE_TEACHER)
			{
				success = true;
				return true;
			}
		}
	else return false;
}

bool Mission1_3 :: update()
{
	 return false;
}


Mission2_1 :: Mission2_1 ()
 : Mission("Mission 2 ")
{
	total = 0;
	curMission = Mission2Type1;
	Map &map = Map::getMap();
	
	bool SetSuccess1 = false;
	SDL_Point SetPos1;
	while(!SetSuccess1)
	{
		Game &game = Game::GetGame();
		SetPos1.x = game.rdEngine()%(map.getRowNum()); 
		SetPos1.y = game.rdEngine()%(map.getColNum());
		if(map.isSpace(SetPos1)) 
		{
			SetSuccess1 = true;
		} 
	}
	TeacherAssistant1* ta1;
	ta1 = new TeacherAssistant1;
	map.placeItem(SetPos1, ta1);
	
	bool SetSuccess2 = false;
	SDL_Point SetPos2;
	while(!SetSuccess2)
	{
		Game &game = Game::GetGame();
		SetPos2.x = game.rdEngine()%(map.getRowNum()); 
		SetPos2.y = game.rdEngine()%(map.getColNum());
		if(map.isSpace(SetPos2)) 
		{
			SetSuccess2 = true;
		} 
	}
	TeacherAssistant2* ta2;
	ta2 = new TeacherAssistant2;
	map.placeItem(SetPos2, ta2);
	
	bool SetSuccess3 = false;
	SDL_Point SetPos3;
	while(!SetSuccess3)
	{
		Game &game = Game::GetGame();
		SetPos3.x = game.rdEngine()%(map.getRowNum()); 
		SetPos3.y = game.rdEngine()%(map.getColNum());
		if(map.isSpace(SetPos3)) 
		{
			SetSuccess3 = true;
		} 
	}
	TeacherAssistant3* ta3;
	ta3 = new TeacherAssistant3;
	map.placeItem(SetPos3, ta3);

}

Mission2_1 :: ~Mission2_1 ()
{
	
}

bool Mission2_1 :: handleEvents(SDL_Event &e)//
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == TA1)
			{
				total++;
			}
			if(e.user.code == TA2)
			{
				total++;
			}
			if(e.user.code == TA3)
			{
				total++;
			}
		}
	if(total == 3)
	{
		success = true;
	}
	return true;
}

bool Mission2_1 :: update()
{
	 return false;
}

/*
Mission2_2 :: Mission2_2 ()
 : Mission("Mission 2 ")
{
	curMission = Mission2Type2;
	Map &map = Map::getMap();
	
	bool SetSuccess = false;
	SDL_Point SetPos;
	while(!SetSuccess)
	{
		Game &game = Game::GetGame();
		SetPos.x = game.rdEngine()%(map->getRowNum()); 
		SetPos.y = game.rdEngine()%(map->getColNum());
		if(map->isSpace(SetPos)) 
		{
			SetSuccess = true;
		} 
	}
	Library* lib;
	lib = new Library;
	map.placeItem(SetPos, lib);

}

Mission2_2 :: ~Mission2_2 ()
{
	
}

bool Mission2_2 :: handleEvents(SDL_Event &e)
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == LIBRARY)
			
			success = true;
		}
}

void Mission2_2 :: update()
{
	 
}
*/

Mission2_3 :: Mission2_3 ()
 : Mission("Mission 2 ")
{
	total = 0;
	curMission = Mission2Type3;
	Map &map = Map::getMap();
	
	bool SetSuccess1 = false;
	SDL_Point SetPos1;
	while(!SetSuccess1)
	{
		Game &game = Game::GetGame();
		SetPos1.x = game.rdEngine()%(map.getRowNum()); 
		SetPos1.y = game.rdEngine()%(map.getColNum());
		if(map.isSpace(SetPos1)) 
		{
			SetSuccess1 = true;
		} 
	}
	WebWork1* web1;
	web1 = new WebWork1;
	map.placeItem(SetPos1, web1);
	
	bool SetSuccess2 = false;
	SDL_Point SetPos2;
	while(!SetSuccess2)
	{
		Game &game = Game::GetGame();
		SetPos2.x = game.rdEngine()%(map.getRowNum()); 
		SetPos2.y = game.rdEngine()%(map.getColNum());
		if(map.isSpace(SetPos2)) 
		{
			SetSuccess2 = true;
		} 
	}
	WebWork2* web2;
	web2 = new WebWork2;
	map.placeItem(SetPos1, web2);
	
	bool SetSuccess3 = false;
	SDL_Point SetPos3;
	while(!SetSuccess3)
	{
		Game &game = Game::GetGame();
		SetPos3.x = game.rdEngine()%(map.getRowNum()); 
		SetPos3.y = game.rdEngine()%(map.getColNum());
		if(map.isSpace(SetPos3)) 
		{
			SetSuccess3 = true;
		} 
	}
	WebWork3* web3;
	web3 = new WebWork3;
	map.placeItem(SetPos1, web3);

}

Mission2_3 :: ~Mission2_3 ()
{
	
}

bool Mission2_3 :: handleEvents(SDL_Event &e)
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == WEBWORK1)
			total++;
		}
		{
			if(e.user.code == WEBWORK2)
			total++;
		}
		{
			if(e.user.code == WEBWORK3)
			total++;
		}
	if(total == 3)
	{
		success = true;
	}
	return true;
}

bool Mission2_3 :: update()
{
	 return false;
}
