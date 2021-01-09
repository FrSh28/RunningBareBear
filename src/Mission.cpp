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

MissionTypes curMission = MissionTotal;

Mission :: Mission(string _name)
 : BasicObject(_name)
{
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
		case Mission2Type1:
			return new Mission2_1();
		case Mission2Type2:
			return new Mission2_2();
		case Mission2Type3:
			return new Mission2_3();			

	}
}

Mission1_1 :: Mission1_1 ()
 : Mission("Mission 1 ")
{
	curMission = Mission1Type1;
	
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
	Sheet* sheet;
	sheet = new Sheet;
	Map &map = Map::getMap();
	Map.placeItem(SetPos, sheet);

}
Mission1_1 :: ~Mission1_1 ()
{
	
	texture = NULL;
}
bool Mission1_1 :: handleEvents(SDL_Event &e)
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == SHEET)
			success = true;
		}
}
bool Mission1_1 :: update()
{
	 
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
		SetPos.x = game.rdEngine()%(map->getRowNum()); 
		SetPos.y = game.rdEngine()%(map->getColNum());
		if(map->isSpace(SetPos)) 
		{
			SetSuccess = true;
		} 
	}
	Library* lib;
	lib = new Library;
	Map.placeItem(SetPos, lib);

}

Mission1_2 :: ~Mission1_2 ()
{
	
	texture = NULL;
}

bool Mission1_2 :: handleEvents(SDL_Event &e)
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == LIBRARY)
			success = true;
		}
}

bool Mission1_2 :: update()
{
	 
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
		SetPos.x = game.rdEngine()%(map->getRowNum()); 
		SetPos.y = game.rdEngine()%(map->getColNum());
		if(map->isSpace(SetPos)) 
		{
			SetSuccess = true;
		} 
	}
	Library* lib;
	lib = new Library;
	Map.placeItem(SetPos, lib);

}

Mission1_3 :: ~Mission1_3 ()
{
	
	texture = NULL;
}

bool Mission1_3 :: handleEvents(SDL_Event &e)
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == LIBRARY)
			success = true;
		}
}

bool Mission1_3 :: update()
{
	 
}


Mission2_1 :: Mission2_1 ()
 : Mission("Mission 2 ")
{
	curMission = Mission1Type2;
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
	Map.placeItem(SetPos, lib);

}

Mission2_1 :: ~Mission2_1 ()
{
	
	texture = NULL;
}

bool Mission2_1 :: handleEvents(SDL_Event &e)
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == LIBRARY)
			success = true;
		}
}

bool Mission2_1 :: update()
{
	 
}


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
	Map.placeItem(SetPos, lib);

}

Mission2_2 :: ~Mission2_2 ()
{
	
	texture = NULL;
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


Mission2_3 :: Mission2_3 ()
 : Mission("Mission 2 ")
{
	curMission = Mission2Type3;
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
	Map.placeItem(SetPos, lib);

}

Mission2_3 :: ~Mission2_3 ()
{
	
	texture = NULL;
}

bool Mission2_3 :: handleEvents(SDL_Event &e)
{
	
	if(e.type == ITEM_USED) 
		{
			if(e.user.code == LIBRARY)
			success = true;
		}
}

bool Mission2_3 :: update()
{
	 
}
