#include <iostream>
#include <cstdlib>
#include <string>
#include "includeSDL.h"
#include "Game.h"
using namespace std;

string PROJECTNAME = "ProjectUnknown";

int main(int argc, char* argv[])
{
	Game game(PROJECTNAME);
	game.Init(1280, 720);
	cout << "Game started!" << endl;
	while(game.isRunning())
	{
		game.HandleEvents();
		game.Update();
		game.Render();
	}
	game.Quit();
	cout << "Game ended!" << endl;

	atexit(SDL_Quit);
	return 0;
}