#include <string>
#include <fstream>
#include <sstream>
#include "includeSDL.h"
#include "Maps.h"
#include "Files.h"
using namespace std;

Maps::Maps()
 : row(0U), col(0U)
{

}

Maps::~Maps()
{

}

void Maps::loadMap(Maps index)
{
	ifstream* inMapFile = openMapFile(Maps index);
	char c;
	string s;
	stringstream ss;
	
	getline(*inMapFile, s);
	ss.str(s);
	ss.clear();
	ss >> row >> c;
	ss >> col >> c;

	for(int i = 0; i < row; ++i)
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
		for(int j = 0; j < col; ++j)
		{
			if(!getline(ss, s, ','))
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load map %d", index);
				row = 0;
				col = 0;
				return;
			}
			if(s.length())
				map[i][j] = stoi(s);
			else
				map[i][j] = 0;
		}
	}
	(*inMapFile).close();
	delete inMapFile;
}