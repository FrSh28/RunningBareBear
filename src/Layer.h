#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <string>
#include "includeSDL.h"
#include "Renderable.h"

class Layer
{
public:
	Layer(std::string _name = "");
	virtual ~Layer() = 0;

	void free();							// destroy all textures and surfaces
	virtual bool handleEvents(SDL_Event &);	// handle events on current layer
	virtual void update();					// update changes on current layer
	virtual void render();					// render elements to mainTexture

	void pushElement(Renderable *);
	void popElement(Renderable *);

	inline std::string getName() const { return name; }
	inline unsigned int getElementsSize() const { return elements.size(); }

protected:
	std::string name;

	SDL_Texture* mainTexture;
	std::vector<Renderable*> elements;
};

#endif	// LAYER_H