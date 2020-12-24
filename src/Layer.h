#ifndef LAYER_H
#define LAYER_H

#include <string>
#include "includeSDL.h"
using namespace std;

class Layer
{
public:
	Layer(string _name = "");
	virtual ~Layer();

	virtual void free();
	virtual void handleEvents(SDL_Event &);
	virtual void update();
	void render();

	inline string getName() const { return name; }
private:
	string name;

	SDL_Texture* mainTexture;
};

#endif	// LAYER_H