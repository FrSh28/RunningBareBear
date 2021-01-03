#include <string>
#include <fstream>
#include "includeSDL.h"
#include "Files.h"
#include "Game.h"
using namespace std;

SDL_Texture *loadImage(Images index)
{
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(Path::P_Images[index].c_str());
	if(surface)
	{
		texture = SDL_CreateTextureFromSurface(Game::GetGame().getRenderer(), surface);
		SDL_FreeSurface(surface);
	}
	return texture;
}

TTF_Font *loadFont(Fonts index, int ptSize)
{
	TTF_Font *font = TTF_OpenFont(Path::P_Fonts[index].c_str(), ptSize);
	return font;
}

Mix_Music *loadMusic(Musics index)
{
	Mix_Music *music = Mix_LoadMUS(Path::P_Musics[index].c_str());
	return music;
}

ifstream *openMapFile(Maps index)
{
	return new ifstream(Path::P_Maps[index], ios_base::in);
}