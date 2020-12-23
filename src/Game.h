#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "Layer.h"
using namespace std;

class Game
{
public:
	Game(string);
	~Game();

	int Init(int width = 1280, int height = 720);	// initialize the game
	int HandleEvents();		// handle changes triggered by SDL events
	int Update();			// update all changes
	int Render();			// render to the screen
	int Quit();				// exit the game

	bool isRunning() const;

private:
	string name;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	bool running;
	vector<Layer> layers;
};

#endif	// GAME_H