#include <iostream>
#include <string>
#include <algorithm>
#include "includeSDL.h"
#include "Game.h"
#include "Layer.h"
using namespace std;

Game *Game::s_gameInstance = NULL;

Game::Game(string _name, unsigned int _width, unsigned int _height,  unsigned int _frameRate)
 : name(_name), width(_width), height(_height), frameRate(_frameRate), window(NULL), renderer(NULL)
	, running(false), layerInsertIndex(0U), startTime(0U), frameCount(0U)
{
	s_gameInstance = this;
}

Game::~Game()
{
	Game::Quit();
}

bool Game::Init()
{
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								width, height, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	if(!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x40, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	//pushLayer(new esssentialLayer);

	return true;
}

void Game::Start(unsigned int _startTime)
{
	startTime = _startTime;
	frameCount = 1;
	running = true;
}

void Game::HandleEvents()
{
	while(SDL_PollEvent(&event) or SDL_GetTicks() - startTime < frameCount * 1000 / frameRate)
	{
		if(event.type == SDL_QUIT)
		{
			running = false;
			return;
		}

		for(auto it = layers.rbegin(); it != layers.rend(); ++it)
		{
			if((*it)->handleEvents(event))	// if handled
				break;
		}
	}
	return;
}

void Game::Update()
{
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		(*it)->update();
	}
	return;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x40, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		(*it)->render();
	}
	SDL_RenderPresent(renderer);
	++frameCount;
	//cout << frameCount << endl;	// debug
	return;
}

void Game::Quit()
{
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		(*it)->free();
		delete *it;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return;
}

void Game::pushLayer(Layer *_layer)
{
	layers.insert(layers.begin() + layerInsertIndex, _layer);
	++layerInsertIndex;
	return;
}

void Game::pushOverlayer(Layer *_overlayer)
{
	layers.push_back(_overlayer);
	return;
}

void Game::popLayer(Layer *_layer)
{
	auto iter = find(layers.begin(), layers.begin() + layerInsertIndex, _layer);
	if (iter != layers.begin() + layerInsertIndex)
	{
		layers.erase(iter);
		--layerInsertIndex;
	}
	return;
}

void Game::popOverlayer(Layer *_overlayer)
{
	auto iter = find(layers.begin() + layerInsertIndex, layers.end(), _overlayer);
	if (iter != layers.end())
	{
		layers.erase(iter);
	}
	return;
}
