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
#include "Character.h"
//#include "Hunter.h"
//#include "Runner.h"

extern Character *createHunter(SDL_Point, SDL_Point);
extern Character *createRunner(SDL_Point, SDL_Point);


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
	void addHunter();
	void free();
	void start();
	bool handleEvents(SDL_Event &);	// return true if handled
	bool update();

	inline bool isSpace(SDL_Point mapPos) const { return map[mapPos.x][mapPos.y] == SPACE; }
	inline bool isWall(SDL_Point mapPos)  const { return map[mapPos.x][mapPos.y] == WALL; }
	inline bool isItem(SDL_Point mapPos)  const { return map[mapPos.x][mapPos.y] == ITEM; }
	bool placeItem(SDL_Point, Item *);	// mapPos
	Item *pickItem(SDL_Point);			// mapPos
	ItemList peekItem(SDL_Point);		// mapPos

	SDL_Point pixelPosTomapPos(SDL_Point);
	SDL_Point mapPosTopixelPos(SDL_Point);

	inline std::vector<SDL_Point> getHuntersMapPos() const { return huntersMapPos; }
	inline SDL_Point getRunnerMapPos() const { return runnerMapPos; }

	inline int getRowNum() const { return rowNum; }
	inline int getColNum() const { return colNum; }
	inline int getWidth()  const { return width; }
	inline int getHeight() const { return height; }
	inline static int getPixelWidth()  { return sc_pixelWidth; }
	inline static int getPixelHeight() { return sc_pixelHeight; }

	inline static Map &getMap() { return *s_mapInstance;}
private:
	void buildMap(BackGround *, BackGround *);

	//std::string name;
	int colNum, rowNum;
	std::vector<std::vector<int>> map;
	int width, height;
	SDL_Point mapPixelPos;
	bool started;
	// for map
	struct SDL_PointComp{ bool operator()(const SDL_Point &, const SDL_Point &); };
	std::map<SDL_Point, Item *, SDL_PointComp> items;

	std::vector<Character *> hunters;
	Character *runner;
	std::vector<SDL_Point> huntersMapPos;
	SDL_Point runnerMapPos;

	Layer *L_ground;
	Layer *L_character;
	Layer *L_front;	// overlayer

	static const int sc_pixelWidth, sc_pixelHeight;
	static Map *s_mapInstance;
};

#endif	// MAP_H