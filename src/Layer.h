#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <string>
#include "includeSDL.h"
#include "Renderable.h"
using namespace std;

class Layer
{
public:
	Layer(string _name = "");
	virtual ~Layer() = 0;

	void free();							// destroy all textures and surfaces
	virtual void handleEvents(SDL_Event &);	// handle events on current layer
	virtual void update();					// update changes on current layer
	virtual void render();					// render elements to mainTexture

	void pushElement(Renderable *);
	void popElement(Renderable *);

	inline string getName() const { return name; }
	inline unsigned int getElementsSize() const { return elements.size(); }

private:
	string name;

	SDL_Texture* mainTexture;
	vector<Renderable*> elements;
};

#endif	// LAYER_H