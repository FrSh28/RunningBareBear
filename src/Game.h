#ifndef GAME_H
#define GAME_H

#include <string>
using namespace std;

class Game
{
public:
	Game(string);
	~Game();

	int Init(int width = 1280, int height = 720);
	int HandleEvents();
	int Update();
	int Render();
	int Quit();

	bool isRunning();

private:
	string name;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	bool running;
};

#endif	//GAME_H