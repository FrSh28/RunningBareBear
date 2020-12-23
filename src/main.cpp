#include <iostream>
#include <cstdlib>
#include <string>
#include "includeSDL.h"
#include "Game.h"
using namespace std;

string PROJECTNAME = "ProjectUnknown";

int main(int argc, char* argv[])
{
	atexit(SDL_Quit);	// for safe exit

	Game game(PROJECTNAME);
	game.Init(1280, 720);
	cout << "Game started!" << endl;

	unsigned int startTime = SDL_GetTicks();
	unsigned int framCount = 1;
	while(game.isRunning())
	{
		while(SDL_GetTicks() - startTime < framCount * 50 / 3)
			game.HandleEvents();
		game.Update();
		game.Render();
		++framCount;
	}
	game.Quit();
	cout << "Game ended!" << endl;

	return 0;
}