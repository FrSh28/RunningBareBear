#include "Files.h"
#include "Game.h"
using namespace std;

namespace Files
{
	string P_Images[IMAGE_COUNT]	= { "../media/image/image.txt",
										};
	string P_Fonts[FONT_COUNT]		= { "../media/font/fonts.txt",
										};
	string P_Musics[MUSIC_COUNT]	= { "../media/music/music.txt",
										};
	string P_Maps[MAP_COUNT]		= { "../media/map/map.txt",
										};

	SDL_Texture *Files::loadedImage[IMAGE_COUNT] = {NULL};
	TTF_Font *Files::loadedFont[FONT_COUNT] = {NULL};
	Mix_Music *Files::loadedMusic[MUSIC_COUNT] = {NULL};
}

SDL_Texture *loadImage(Images index)
{
	if(loadedImage[index])
		return loadedImage[index];

	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(P_Images[index].c_str());
	if(surface)
	{
		texture = SDL_CreateTextureFromSurface(Game::GetGame().getRenderer(), surface);
		SDL_FreeSurface(surface);
	}
	return texture;
}

TTF_Font *loadFont(Fonts index, int ptSize)
{
	if(loadedFont[index])
		return loadedFont[index];

	TTF_Font *font = TTF_OpenFont(P_Fonts[index].c_str(), ptSize);
	return font;
}

Mix_Music *loadMusic(Musics index)
{
	if(loadedMusic[index])
		return loadedMusic[index];

	Mix_Music *music = Mix_LoadMUS(P_Musics[index].c_str());
	return music;
}

ifstream *openMapFile(Maps index)
{
	return new ifstream(P_Maps[index], ios_base::in);
}

void freeImage(Images index)
{
	if(loadedImage[index])
	{
		SDL_DestroyTexture(loadedImage[index]);
		loadedImage[index] = NULL;
	}
}

void freeFont(Fonts index)
{
	if(loadedFont[index])
	{
		TTF_CloseFont(loadedFont[index]);
		loadedFont[index] = NULL;
	}
}

void freeMusic(Musics index)
{
	if(loadedMusic[index])
	{
		Mix_FreeMusic(loadedMusic[index]);
		loadedMusic[index] = NULL;
	}
}
