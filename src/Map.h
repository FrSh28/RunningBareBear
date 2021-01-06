#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <map>
#include "includeSDL.h"
#include "BasicObject.h"
#include "Layer.h"
#include "Files.h"
#include "Item.h"

enum ObjOnMap
{
	SPACE,
	WALL,
	ITEM,
};

class Map : public BasicObject
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
	int rowNum, colNum;
	std::vector<std::vector<int>> map;
	int width, height;
	// for map
	struct SDL_PointComp{ bool operator()(const SDL_Point &, const SDL_Point &); };
	std::map<SDL_Point, Item *, SDL_PointComp> items;

	Layer *ground;
	Layer *front;	// overlayer

	static const int sc_pixelWidth, sc_pixelHeight;
	static Map *s_mapInstance;
};

#endif	// MAP_H