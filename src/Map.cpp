#include <fstream>
#include <sstream>
#include "Map.h"
#include "Game.h"
using namespace std;

const int Map::sc_pixelWidth = 50, Map::sc_pixelHeight = 40;
Map *Map::s_mapInstance = NULL;

Map::Map(Maps index, string _name)
 : name(_name), rowNum(0), colNum(0), width(0), height(0), L_ground(NULL), L_character(NULL), L_front(NULL)
{
	s_mapInstance = this;
	loadMap(index);
	Game &game = Game::GetGame();
	game.setGameMap(this);
	
	L_ground = new Layer("MapGround", false);
	game.pushLayer(L_ground);
	L_character = new Layer("Character", false);
	game.pushLayer(L_character);
	L_front = new Layer("MapFront", false);
	game.pushOverlayer(L_front);
	/*
	for()
	{
		hunters.push_back(new Hunter(mapPos, pixelPos));
		character.pushElement(hunters.back());
	}
	runner = new Runner(mapPos, pixelPos);
	character.pushElement(runner);
	*/
}

Map::~Map()
{
	free();
}

void Map::loadMap(Maps index)
{
	ifstream* inMapFile = openMapFile(index);
	char c;
	string s;
	stringstream ss;
	
	getline(*inMapFile, s);
	ss.str(s);
	ss.clear();
	ss >> rowNum >> c;
	ss >> colNum >> c;

	int n;
	for(int i = 0; i < rowNum; ++i)
	{
		if(!getline(*inMapFile, s))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load map %d", index);
			rowNum = 0;
			colNum = 0;
			return;
		}
		ss.str(s);
		ss.clear();
		vector<int> tmpV;
		for(int j = 0; j < colNum; ++j)
		{
			if(!getline(ss, s, ','))
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load map %d", index);
				rowNum = 0;
				colNum = 0;
				return;
			}
			if(s.length())
				n = stoi(s);
			else
				n = 0;
			tmpV.push_back(n);
		}
		map.push_back(tmpV);
	}
	(*inMapFile).close();
	delete inMapFile;

	width = rowNum * sc_pixelWidth;
	height = colNum * sc_pixelHeight;
}

void Map::free()
{
	Game &game = Game::GetGame();
	game.popOverlayer(L_front);
	delete L_front;
	L_front = NULL;
	game.popLayer(L_character);
	delete L_character;
	L_character = NULL;
	game.popLayer(L_ground);
	delete L_ground;
	L_ground = NULL;
	/*
	hunters.clear();	// already deleted by L_character
	runner = NULL;		// already deleted by L_character
	*/
	// delete items
	game.setGameMap(NULL);
}

bool Map::handleEvents(SDL_Event &event)
{
	return false;
}

void Map::update()
{/*
	for(long long unsigned int i = 0; i < hunters.size(); ++i)
	{
		huntersMapPos[i] = pixelPosTomapPos(hunters[i]->getPixelPos());
	}
	runnerMapPos = pixelPosTomapPos(runner->getPixelPos());*/
}

bool Map::placeItem(SDL_Point pos, Item *item)	// mapPos
{
	if(!isSpace(pos) or item == NULL)
		return false;
	else
	{
		map[pos.x][pos.y] = ITEM;
		//item->setPosOnMap(pos);
		items.insert({pos, item});
		L_ground->pushElement(item);
		return true;
	}
}

Item *Map::pickItem(SDL_Point pos)		// mapPos
{
	if(!isItem(pos))
		return NULL;
	else
	{
		Item *tmp = items[pos];
		items.erase(pos);
		map[pos.x][pos.y] = SPACE;
		L_ground->popElement(tmp);
		return tmp;
	}
}

ItemList Map::peekItem(SDL_Point pos)	// mapPos
{
	if(!isItem(pos))
		return BAD_ITEM;
	else
	{
		return BAD_ITEM;//items[pos]->getItemType();
	}
}

SDL_Point Map::pixelPosTomapPos(SDL_Point pixelPos)
{
	return SDL_Point({pixelPos.x / sc_pixelWidth, pixelPos.y / sc_pixelHeight});
}

SDL_Point Map::mapPosTopixelPos(SDL_Point mapPos)
{
	return SDL_Point({mapPos.x * sc_pixelWidth, mapPos.y * sc_pixelHeight});
}

bool Map::SDL_PointComp::operator()(const SDL_Point &lhs, const SDL_Point &rhs)
{
	if(lhs.x != rhs.x)
		return lhs.x < rhs.x;
	else
		return lhs.y < rhs.y;
}