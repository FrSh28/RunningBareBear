#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "includeSDL.h"
#include "Layer.h"
using namespace std;

class Game
{
public:
	Game(string, unsigned int _width = 1280, unsigned int _height = 720, unsigned int _frameRate = 60);
	~Game();

	bool Init();				// initialize the game
	void Start(unsigned int);	// start the game
	void HandleEvents();		// handle changes triggered by SDL events
	void Update();				// update all changes
	void Render();				// render to the screen
	void Quit();				// exit the game

	void pushLayer(Layer *);		// push new layer to layers
	void pushOverlayer(Layer *);	// push new overlayer to layers
	void popLayer(Layer *);		// pop layer from layers
	void popOverlayer(Layer *);	// pop overlayer from layers

	inline bool isRunning() const { return running; }
	inline string getName() const { return name; }
	inline unsigned int getWidth()  const { return width; }
	inline unsigned int getHeight() const { return height; }
	inline unsigned int getFrameRate() const { return frameRate; }
	inline SDL_Renderer *getRenderer() const { return renderer; }
	inline unsigned int getLayersSize() const { return layers.size(); }

	inline static Game &GetGame() { return *s_gameInstance; }

private:
	string name;
	unsigned int width;
	unsigned int height;
	unsigned int frameRate;

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	bool running;

	vector<Layer*> layers;
	unsigned int layerInsertIndex;

	unsigned int startTime;
	unsigned int frameCount;

	static Game *s_gameInstance;
};

#endif	// GAME_H