#include <fstream>
#include <sstream>
#include "Map.h"
#include "Game.h"
#include "UserEvent.h"
using namespace std;

const int Map::sc_pixelWidth = 100, Map::sc_pixelHeight = 80;
Map *Map::s_mapInstance = NULL;

Map::Map(Maps index, string _name)
 : name(_name), colNum(0), rowNum(0), width(0), height(0), mapPixelPos({0, 0}), L_ground(NULL), L_interact(NULL), L_front(NULL)
{
	s_mapInstance = this;
	loadMap(index);
	////////////
	L_ground = new Layer("MapGround", false);
	game.pushLayer(L_ground);
	L_interact = new Layer("Interact", false);
	game.pushLayer(L_interact);
	L_front = new Layer("MapFront", false);
	game.pushOverlayer(L_front);
	///////////
	for(int i = 0; i < 10; ++i)
		addHunter();

	SDL_Point tmpMapPos, tmpPixelPos;
	Game &game = Game::GetGame();
	do
	{
		tmpMapPos.x = game.rdEngine() % rowNum;
		tmpMapPos.y = game.rdEngine() % colNum;
	}while(!isSpace(tmpMapPos) or huntersMapPos.end() != find(huntersMapPos.begin(), huntersMapPos.end(), tmpMapPos));
	tmpPixelPos = mapPosTopixelPos(tmpMapPos);
	tmpPixelPos.x += sc_pixelWidth / 2;
	tmpPixelPos.y += sc_pixelHeight / 2;
	runner = new Runner(tmpMapPos, tmpPixelPos);
	character->pushElement(runner);
	update();
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

	width = colNum * sc_pixelWidth;
	height = rowNum * sc_pixelHeight;
}

void Map::addHunter()
{
	SDL_Point tmpMapPos, tmpPixelPos;
	Game &game = Game::GetGame();
	do
	{
		tmpMapPos.x = game.rdEngine() % rowNum;
		tmpMapPos.y = game.rdEngine() % colNum;
	}while(!isSpace(tmpMapPos) or tmpMapPos == runnerMapPos or huntersMapPos.end() != find(huntersMapPos.begin(), huntersMapPos.end(), tmpMapPos));
	tmpPixelPos = mapPosTopixelPos(tmpMapPos);
	tmpPixelPos.x += sc_pixelWidth / 2;
	tmpPixelPos.y += sc_pixelHeight / 2;
	hunters.push_back(new Hunter(tmpMapPos, tmpPixelPos));
	character->pushElement(hunters.back());
	huntersMapPos.push_back(tmpMapPos);
}

void Map::free()
{
	Game &game = Game::GetGame();
	game.popOverlayer(L_front);
	delete L_front;
	L_front = NULL;
	game.popLayer(L_interact);
	delete L_interact;
	L_interact = NULL;
	game.popLayer(L_ground);
	delete L_ground;
	L_ground = NULL;
	items.clear();		// already deleted by L_interact
	hunters.clear();	// already deleted by L_interact
	runner = NULL;		// already deleted by L_interact
	game.setGameMap(NULL);
}

bool Map::handleEvents(SDL_Event &event)
{
	return false;
}

void Map::update()
{
	SDL_Point tmpPixelPos, movePixelPos;
	Game &game = Game::GetGame();
	int scrWidth = game.getWidth(), scrHeight = game.getHeight();
	tmpPixelPos = runner->getPixelPos();
	runnerMapPos = pixelPosTomapPos(tmpPixelPos);
	mapPixelPos = SDL_Point({scrWidth/2 - tmpPixelPos.x, scrHeight/2 - tmpPixelPos.y});
	//runner->setScreenPos(SDL_Point({mapPixelPos.x + tmpPixelPos.x, mapPixelPos.y + tmpPixelPos.y}));
	for(long long unsigned int i = 0; i < hunters.size(); ++i)
	{
		huntersMapPos[i] = pixelPosTomapPos(hunters[i]->getPixelPos());
		if(huntersMapPos[i] == runnerMapPos)
			createUserEvent(CAUGHT, 0);
		//hunters[i]->setScreenPos(SDL_Point({mapPixelPos.x + tmpPixelPos.x, mapPixelPos.y + tmpPixelPos.y}));
	}
	L_ground->setRectViewPos();
	L_interact->setRectViewPos();
	L_front->setRectViewPos();
}

bool Map::placeItem(SDL_Point pos, Item *item)	// mapPos
{
	if(!isSpace(pos) or item == NULL)
		return false;
	else
	{
		map[pos.x][pos.y] = ITEM;
		SDL_Point tmp = mapPosTopixelPos(pos);
		item->setRectOnScreen(SDL_Rect({tmp.x, tmp.y, sc_pixelWidth, sc_pixelHeight}));
		items.insert({pos, item});
		L_interact->pushElement(item);
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
		L_interact->popElement(tmp);
		return tmp;
	}
}

ItemList Map::peekItem(SDL_Point pos)	// mapPos
{
	if(!isItem(pos))
		return BAD_ITEM;
	else
	{
		return items[pos]->getItemType();
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

SDL_Point pixelPosToscreenPos(SDL_Point pixelPos)
{

}

bool Map::SDL_PointComp::operator()(const SDL_Point &lhs, const SDL_Point &rhs)
{
	if(lhs.x != rhs.x)
		return lhs.x < rhs.x;
	else
		return lhs.y < rhs.y;
}