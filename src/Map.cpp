#include <string>
#include <fstream>
#include <sstream>
#include "includeSDL.h"
#include "Map.h"
#include "Files.h"
using namespace std;

Map::Map()
 : row(0U), col(0U)
{

}

Map::~Map()
{

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
	ss >> row >> c;
	ss >> col >> c;

	int n;
	for(unsigned int i = 0; i < row; ++i)
	{
		if(!getline(*inMapFile, s))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load map %d", index);
			row = 0;
			col = 0;
			return;
		}
		ss.str(s);
		ss.clear();
		vector<int> tmpV;
		for(unsigned int j = 0; j < col; ++j)
		{
			if(!getline(ss, s, ','))
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load map %d", index);
				row = 0;
				col = 0;
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
}