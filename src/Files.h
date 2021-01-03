#ifndef FILES_H
#define FILES_H

#include <string>
#include <fstream>
#include "includeSDL.h"

enum Images
{
	SAMPLE_IMAGE,
	IMAGE_COUNT,
};

enum Fonts
{
	SAMPLE_FONT,
	FONT_COUNT,
};

enum Musics
{
	SAMPLE_MUSIC,
	MUSIC_COUNT,
};

enum Maps
{
	SAMPLE_MAP,
	MAP_COUNT,
};

SDL_Texture *loadImage(Images index);
TTF_Font *loadFont(Fonts index, int ptSize);
Mix_Music *loadMusic(Musics index);
std::ifstream *openMapFile(Maps index);

namespace Files
{
	extern std::string P_Images[IMAGE_COUNT];
	extern std::string P_Fonts[FONT_COUNT];
	extern std::string P_Musics[MUSIC_COUNT];
	extern std::string P_Maps[MAP_COUNT];
}

#endif	// FILES_H