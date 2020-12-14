#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_bgi.h>
using namespace std;

int main(int argc, char* argv[])
{
	initwindow(800, 600);
	cleardevice();

	circle(100,100,100);
	cout << "TEST" << endl;

	getch();
	closegraph();
	return 0;
}