#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include "includeSDL.h"
#include "Files.h"

class Map
{
public:
	Map();
	~Map();

	void loadMap(Maps index);

private:
	unsigned int row, col;
	std::vector<std::vector<int>> map;
};

#endif	// MAP_H