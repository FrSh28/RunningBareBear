#include <algorithm>
#include "Layer.h"
#include "Game.h"
#include "Files.h"
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
	else
	{
		SDL_SetTextureBlendMode(mainTexture, SDL_BLENDMODE_BLEND);
	}
}

Layer::~Layer()
{
	free();
}

void Layer::free()
{
	for(auto it = elements.begin(); it != elements.end(); ++it)
	{
		if(*it)
		{
			delete (*it);
			*it = NULL;
		}
	}
	elements.clear();
	if(mainTexture)
	{
		SDL_DestroyTexture(mainTexture);
		mainTexture = NULL;
	}
}

bool Layer::handleEvents(SDL_Event &e)
{
	for(auto it = elements.rbegin(); it != elements.rend(); ++it)
	{
		if((*it)->handleEvents(e))	// if handled
			return true;
	}
	return false;
}

void Layer::update()
{
	for(auto it = elements.begin(); it != elements.end(); ++it)
	{
		(*it)->update();
	}
}

void Layer::render()
{
	SDL_Renderer *renderer = Game::GetGame().getRenderer();
	SDL_SetRenderTarget(renderer, mainTexture);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0x00);
	SDL_RenderClear(renderer);
	for(auto it = elements.begin(); it != elements.end(); ++it)
	{
		if((*it)->getTexture() and (*it)->getPosOnTexture() and (*it)->getPosOnWindow())
			SDL_RenderCopy(renderer, (*it)->getTexture(), (*it)->getPosOnTexture(), (*it)->getPosOnWindow());
	}
}

void Layer::pushElement(BasicObject *_element)
{
	elements.push_back(_element);
}

void Layer::popElement(BasicObject *_element)
{
	auto iter = find(elements.begin(), elements.begin(), _element);
	if (iter != elements.end())
	{
		elements.erase(iter);
	}
}
