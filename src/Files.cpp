#include "Files.h"
#include "Game.h"
using namespace std;
/*
HUNTER_IMAGE,

	INFOR_IMAGE,
	MISSION_1_1_IMAGE,
	MISSION_1_2_IMAGE,
	MISSION_1_3_IMAGE,
	MISSION_2_1_IMAGE,
	MISSION_2_2_IMAGE,
*/

namespace Files
{
	string P_Images[IMAGE_COUNT];
	P_Images[SAMPLE_IMAGE] = "../media/image/image.txt";
	P_Images[START_BUTTON_IMAGE] = "../media/image/StartButton_512_512.png";
	P_Images[INTRO_BUTTON_IMAGE] = "../media/image/Intro.png";
	P_Images[PAUSE_BUTTON_IMAGE] = "../media/image/Pause.png";
	P_Images[MISSION_BUTTON_IMAGE] = "../media/image/Mission.png";
	P_Images[RESUME_BUTTON_IMAGE] = "../media/image/Resume.png";
	P_Images[LEAVE_BUTTON_IMAGE] = "../media/image/Leave.png";
	P_Images[RESTART_BUTTON_IMAGE] = "../media/image/Restart.png";
	P_Images[OK_BUTTON_IMAGE] = "../media/image/Ok.png";
	P_Images[INTRO_IMAGE] = "../media/image/";//
	P_Images[MISSION_1_1_IMAGE] = "../media/image/";//
	P_Images[MISSION_1_2_IMAGE] = "../media/image/";//
	P_Images[MISSION_1_3_IMAGE] = "../media/image/";//
	P_Images[MISSION_2_1_IMAGE] = "../media/image/";//
	P_Images[MISSION_2_2_IMAGE] = "../media/image/";//
	SDL_Texture *loadedImage[IMAGE_COUNT] = {NULL};

	//string P_Fonts[FONT_COUNT];
	//P_Fonts[SAMPLE_FONT] = "../media/font/fonts.txt";
	//TTF_Font *loadedFont[FONT_COUNT] = {NULL};

	string P_Musics[MUSIC_COUNT];
	P_Musics[SAMPLE_MUSIC] = "../media/music/music.txt";
	Mix_Music *loadedMusic[MUSIC_COUNT] = {NULL};

	string P_Maps[MAP_COUNT];
	P_Maps[SAMPLE_MAP] = "../media/map/map.txt";
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
