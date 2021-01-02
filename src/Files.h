#ifndef FILES_H
#define FILES_H

#include <string>
#include "includeSDL.h"

SDL_Texture *loadSprite(Sprites index);
SDL_Texture *loadMap(Maps index);
Mix_Music *loadMusic(Musics index);

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

SDL_Texture *loadMedia(int type, int index)
{

}

//SDL_Texture *tex = IMG_LoadTexture(SDL_Renderer *renderer, const char *file);
//TTF_Font *font = TTF_OpenFont(const char *file, int ptsize);
//Mix_Music *mus = Mix_LoadMUS(const char *file);

#endif	// FILES_H