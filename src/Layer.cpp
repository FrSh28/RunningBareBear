#include <string>
#include <algorithm>
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

void Layer::free()
{
	for(auto it = elements.begin(); it != elements.end(); ++it)
	{
		delete (*it);
	}
	SDL_DestroyTexture(mainTexture);
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

}

void Layer::render()
{
	for(auto it = elements.begin(); it != elements.end(); ++it)
	{
		//render (*it) onto mainTexture
	}
}

void Layer::pushElement(Renderable *_element)
{
	elements.push_back(_element);
	return;
}

void Layer::popElement(Renderable *_element)
{
	auto iter = find(elements.begin(), elements.begin(), _element);
	if (iter != elements.begin())
	{
		elements.erase(iter);
	}
	return;
}

