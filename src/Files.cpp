#include "Files.h"
#include "Game.h"
using namespace std;

namespace Files
{
	string P_Images[IMAGE_COUNT]	= { "../media/image/image.txt",
										"../media/image/Hunter_32_32.png",
										"../media/image/StartButton_512_512.png",
										"../media/image/Intro.png",
										"../media/image/Pause.png",
										"../media/image/Mission.png",
										"../media/image/Resume.png",
										"../media/image/Leave.png",
										"../media/image/Restart.png",
										"../media/image/Ok.png",
										"../media/image/",
										"../media/image/",
										"../media/image/",
										"../media/image/",
										"../media/image/",
										"../media/image/",
										"../media/image/",
										};

	//string P_Fonts[FONT_COUNT]	= { "../media/font/fonts.txt",};

	string P_Musics[MUSIC_COUNT]	= { "../media/music/music.txt",
										};

	string P_Maps[MAP_COUNT]		= { "../media/map/map.txt",
										"../media/map/map01.csv",
										"../media/map/map02.csv",
										"../media/map/map03.csv",
										"../media/map/map04.csv",
										};

	SDL_Texture *loadedImage[IMAGE_COUNT] = {NULL};
	//TTF_Font *loadedFont[FONT_COUNT] = {NULL};
	Mix_Music *loadedMusic[MUSIC_COUNT] = {NULL};
}

SDL_Texture *loadImage(Images index)
{
	if(Files::loadedImage[index])
		return Files::loadedImage[index];

	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(Files::P_Images[index].c_str());
	if(surface)
	{
		texture = SDL_CreateTextureFromSurface(Game::GetGame().getRenderer(), surface);
		SDL_FreeSurface(surface);
	}
	Files::loadedImage[index] = texture;
	return texture;
}
/*
TTF_Font *loadFont(Fonts index, int ptSize)
{
	if(Files::loadedFont[index])
		return Files::loadedFont[index];

	TTF_Font *font = TTF_OpenFont(Files::P_Fonts[index].c_str(), ptSize);
	Files::Files::loadedFont[index] = font;
	return font;
}
*/
Mix_Music *loadMusic(Musics index)
{
	if(Files::loadedMusic[index])
		return Files::loadedMusic[index];

	Mix_Music *music = Mix_LoadMUS(Files::P_Musics[index].c_str());
	Files::loadedMusic[index] = music;
	return music;
}

ifstream *openMapFile(Maps index)
{
	return new ifstream(Files::P_Maps[index], ios_base::in);
}

void freeImage(Images index)
{
	if(Files::loadedImage[index])
	{
		SDL_DestroyTexture(Files::loadedImage[index]);
		Files::loadedImage[index] = NULL;
	}
}
/*
void freeFont(Fonts index)
{
	if(Files::loadedFont[index])
	{
		TTF_CloseFont(Files::loadedFont[index]);
		Files::loadedFont[index] = NULL;
	}
}
*/
void freeMusic(Musics index)
{
	if(Files::loadedMusic[index])
	{
		Mix_FreeMusic(Files::loadedMusic[index]);
		Files::loadedMusic[index] = NULL;
	}
}
