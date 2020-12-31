#ifndef FILES_H
#define FILES_H

#include <string>

enum Sprites
{

};

enum Maps
{
	
};

enum Fonts
{
	
};

enum Musics
{
	
};

namespace Path
{
	std::string P_Sprites[] = {"../media/image/"};
	std::string P_Maps[] = {"../media/map/"};
	std::string P_Fonts[] = {"../media/font/"};
	std::string P_Musics[] = {"../media/audio/"};
}

//SDL_Texture *tex = IMG_LoadTexture(SDL_Renderer *renderer, const char *file);

#endif	// FILES_H