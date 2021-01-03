#include <string>
#include <fstream>
#include "includeSDL.h"
#include "Files.h"
#include "Game.h"
using namespace std;

namespace Files
{
	string P_Images[IMAGE_COUNT]	= { "../media/image/",
										};
	string P_Fonts[FONT_COUNT]		= { "../media/font/",
										};
	string P_Musics[MUSIC_COUNT]	= { "../media/music/",
										};
	string P_Maps[MAP_COUNT]		= { "../media/map/",
										};
}

SDL_Texture *loadImage(Images index)
{
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(Files::P_Images[index].c_str());
	if(surface)
	{
		texture = SDL_CreateTextureFromSurface(Game::GetGame().getRenderer(), surface);
		SDL_FreeSurface(surface);
	}
	return texture;
}

TTF_Font *loadFont(Fonts index, int ptSize)
{
	TTF_Font *font = TTF_OpenFont(Files::P_Fonts[index].c_str(), ptSize);
	return font;
}

Mix_Music *loadMusic(Musics index)
{
	Mix_Music *music = Mix_LoadMUS(Files::P_Musics[index].c_str());
	return music;
}

ifstream *openMapFile(Maps index)
{
	return new ifstream(Files::P_Maps[index], ios_base::in);
}