#ifndef MAPS_H
#define MAPS_H

#include <string>
#include <vector>
#include "includeSDL.h"
#include "Files.h"

class Maps
{
public:
	Maps();
	~Maps();

	void loadMaps(Maps index);

private:
	unsigned int row, col;
	vector<vector<int>> map;
};

#endif	// MAPS_H