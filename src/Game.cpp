#include <iostream>
#include <algorithm>
#include <random>
#include "Game.h"
#include "Layer.h"
#include "Map.h"
#include "UserEvent.h"
using namespace std;

Game *Game::s_gameInstance = NULL;

Game::Game(string _name, unsigned int _width, unsigned int _height,  unsigned int _frameRate)
 : name(_name), width(_width), height(_height), frameRate(_frameRate), running(false), state(STARTMENU),
	window(NULL), renderer(NULL), layerInsertIndex(0U), gameMap(NULL), startTime(0U), frameCount(0U)
{
	random_device rd;
	rdEngine.seed(rd());
	s_gameInstance = this;
}

Game::~Game()
{
	Quit();
}

bool Game::Init()
{
	// SDL
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}

	// SDL_ttf
	if(!TTF_WasInit())
	{
		if(TTF_Init() < 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init: Failed to init required font support: %s", TTF_GetError());
			return false;
		}
	}

	// SDL_mixer
	int Mix_flags = MIX_INIT_FLAC|MIX_INIT_MOD|MIX_INIT_MP3|MIX_INIT_OGG;
	if(Mix_Init(Mix_flags) ^ Mix_flags)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init: Failed to init required audio support: %s", Mix_GetError());
		return false;
	}

	// SDL_image
	int IMG_flags = IMG_INIT_JPG|IMG_INIT_PNG;
	if(IMG_Init(IMG_flags) ^ IMG_flags)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init: Failed to init required image support: %s", IMG_GetError());
		return false;
	}

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, 40,
								width, height, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	if(!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
	if(!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x40, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	// for testing
	pushLayer(new Layer("TestLayer"));
	//layers[0]->pushElement(someBasicObject);
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
	bool handled = false;
	while(SDL_PollEvent(&event) or SDL_GetTicks() - startTime < frameCount * 1000 / frameRate)
	{
		if(event.type == GAMESTATE_CHANGE)
		{
			GameState tmp = GameState(event.user.code);
			switch(tmp)
			{
				case START:
					break;
				case PAUSE:
					break;
				case RESUME:
					break;
				default:
					break;
			}
		}
		switch(event.type)
		{
			case SDL_QUIT:
				running = false;
				return;	// func
			default:
				for(auto it = layers.rbegin(); it != layers.rend(); ++it)
				{
					if((*it)->isActive())
						if((*it)->handleEvents(event))	// if handled
						{
							handled = true;
							break;	// for
						}
				}
				if(!handled and gameMap)
					gameMap->handleEvents(event);
				break;	// switch
		}
	}
}

void Game::Update()
{
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		if((*it)->isActive())
			(*it)->update();
	}
	if(gameMap)
		gameMap->update();
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
		if((*it)->isActive())
			SDL_RenderCopy(renderer, (*it)->getTexture(), NULL, NULL);
	}
	SDL_RenderPresent(renderer);
	++frameCount;
	//cout << frameCount << endl;	// debug
}

void Game::Quit()
{
	delete gameMap;
	gameMap = NULL;

	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
	layers.clear();
	if(renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if(window)
	{
			SDL_DestroyWindow(window);
		window = NULL;
	}
	IMG_Quit();
	while(Mix_Init(0))
		Mix_Quit();
	if(TTF_WasInit())
		TTF_Quit();
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

void Game::popTopOverlayer()
{
	layers.pop_back();
}
