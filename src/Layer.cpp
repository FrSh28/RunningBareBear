#include <string>
#include "includeSDL.h"
#include "Layer.h"
#include "Game.h"
using namespace std;

Layer::Layer(string _name)
 : name(_name), mainTexture(NULL)
{
	Game &game = Game::GetGame();
	mainTexture = SDL_CreateTexture(game.getRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, game.getWidth(), game.getHeight());
	if(!mainTexture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture for layer %s: %s", name.c_str(), SDL_GetError());
	}
}

Layer::~Layer()
{
	free();
	// free the textures
}

void Layer::free()
{

}

void Layer::handleEvents(SDL_Event &e)
{

}

void Layer::update()
{
	
}

void Layer::render()
{

}
