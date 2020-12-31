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
	Quit();
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
	SDL_RenderPresent(renderer);

	int IMG_flags = IMG_INIT_JPG|IMG_INIT_PNG;
	if((IMG_Init(IMG_flags) & IMG_flags) != IMG_flags)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init: Failed to init required image support: %s", IMG_GetError());
		return false;
	}

	int Mix_flags = MIX_INIT_FLAC|MIX_INIT_MOD|MIX_INIT_MP3|MIX_INIT_OGG;
	if((Mix_Init(Mix_flags) & Mix_flags) != Mix_flags)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init: Failed to init required audio support: %s", Mix_GetError());
		return false;
	}

	// for testing
	Layer *l = new Layer("TestLayer");
	pushLayer(l);
	//layers[0]->pushElement(someRenderableObj);
	// for testing

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
			break;	// while
		}

		for(auto it = layers.rbegin(); it != layers.rend(); ++it)
		{
			if((*it)->handleEvents(event))	// if handled
				break;	// for
		}
	}
}

void Game::Update()
{
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		(*it)->update();
	}
}

void Game::Render()
{
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		(*it)->render();
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x40, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		SDL_RenderCopy(renderer, (*it)->getTexture(), NULL, NULL);
	}
	SDL_RenderPresent(renderer);
	++frameCount;
	//cout << frameCount << endl;	// debug
}

void Game::Quit()
{
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		if(*it)
		{
			(*it)->free();
			delete *it;
			*it = NULL;
		}		
	}
	layers.clear();
	while(Mix_Init(0))
		Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::pushLayer(Layer *_layer)
{
	layers.insert(layers.begin() + layerInsertIndex, _layer);
	++layerInsertIndex;
}

void Game::pushOverlayer(Layer *_overlayer)
{
	layers.push_back(_overlayer);
}

void Game::popLayer(Layer *_layer)
{
	auto iter = find(layers.begin(), layers.begin() + layerInsertIndex, _layer);
	if (iter != layers.begin() + layerInsertIndex)
	{
		layers.erase(iter);
		--layerInsertIndex;
	}
}

void Game::popOverlayer(Layer *_overlayer)
{
	auto iter = find(layers.begin() + layerInsertIndex, layers.end(), _overlayer);
	if (iter != layers.end())
	{
		layers.erase(iter);
	}
}
