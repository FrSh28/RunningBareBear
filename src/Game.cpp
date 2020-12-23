#include <string>
#include "includeSDL.h"
#include "Game.h"
#include "Layer.h"
using namespace std;

Game::Game(string _name)
 : name(_name), window(NULL), renderer(NULL), running(false)
{}

Game::~Game()
{}

int Game::Init(int width, int height)
{
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								width, height, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	if(!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		return -1;
	}
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

	running = true;
	return 0;
}

int Game::HandleEvents()
{
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			running = false;
			return 0;
		}

		for(auto it = layers.end(); it != layers.begin(); --it)
		{
			//it->handleEvents();
		}
	}
	return 0;
}

int Game::Update()
{
	return 0;
}

int Game::Render()
{
	SDL_RenderClear(renderer);
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		//it->render();
	}
	SDL_RenderPresent(renderer);
	return 0;
}

int Game::Quit()
{
	running = false;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

bool Game::isRunning() const
{
	return running;
}