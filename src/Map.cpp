#include <fstream>
#include <sstream>
#include "Map.h"
#include "Game.h"
using namespace std;

const int Map::sc_pixelWidth = 50, Map::sc_pixelHeight = 40;

Map::Map(Maps index, string _name)
 : name(_name), rowNum(0), colNum(0), width(0), height(0), ground(new Layer("MapGround")), front(new Layer("MapFront"))
{
	s_mapInstance = this;
	loadMap(index);
	Game &game = Game::GetGame();
	game.pushLayer(ground);
	game.pushOverlayer(front);
}

Map::~Map()
{}

bool Map::isSpace(SDL_Point pos)		// mapPos
{
	return map[pos.x][pos.y] == SPACE;
}

bool Map::isWall(SDL_Point pos)			// mapPos
{
	return map[pos.x][pos.y] == WALL;
}

bool Map::isItem(SDL_Point pos)			// mapPos
{
	return map[pos.x][pos.y] == ITEM;
}

bool Map::placeItem(SDL_Point pos, Item *item)	// mapPos
{
	if(!isSpace(pos))
		return false;
	else
	{
		map[pos.x][pos.y] = ITEM;
		//item->setPosOnMap(pos);
		items.insert({pos, item});
		ground->pushElement(item);
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
		ground->popElement(tmp);
		return tmp;
	}
}

ItemList Map::getItem(SDL_Point pos)	// mapPos
{
	if(!isItem(pos))
		return ItemList(-1);
	else
	{
		//return items[pos]->getType();
		return ItemList(0);
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

// for map
bool comp(const SDL_Point &lhs, const SDL_Point &rhs)
{
	if(lhs.x < rhs.x)
		return true;
	else if(lhs.x > rhs.x)
		return false;
	else if(lhs.x == rhs.x)
	{
		if(lhs.y < rhs.y)
			return true;
		else
			return false;
	}
	return false;
}