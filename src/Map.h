#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <map>
#include "includeSDL.h"
#include "Layer.h"
#include "Files.h"
#include "Item.h"

enum ObjOnMap
{
	SPACE,
	WALL,
	ITEM,
};

// for map
bool comp(const SDL_Point &, const SDL_Point &);

class Map
{
public:
	Map(Maps index, std::string _name = "");
	~Map();

	void loadMap(Maps index);
	bool isSpace(SDL_Point);			// mapPos
	bool isWall(SDL_Point);				// mapPos
	bool isItem(SDL_Point);				// mapPos
	bool placeItem(SDL_Point, Item *);	// mapPos
	Item *pickItem(SDL_Point);			// mapPos
	ItemList getItem(SDL_Point);		// mapPos

	SDL_Point pixelPosTomapPos(SDL_Point);
	SDL_Point mapPosTopixelPos(SDL_Point);

	inline int getRowNum() const { return rowNum; }
	inline int getColNum() const { return colNum; }
	inline int getWidth()  const { return width; }
	inline int getHeight() const { return height; }

	inline static Map &getMap() { return *s_mapInstance;}
private:
	std::string name;
	int rowNum, colNum;
	std::vector<std::vector<int>> map;
	int width, height;
	std::map<SDL_Point, Item *, decltype(comp)*> items;

	Layer *ground;
	Layer *front;	// overlayer

	static const int sc_pixelWidth, sc_pixelHeight;
	static Map *s_mapInstance;
};

#endif	// MAP_H