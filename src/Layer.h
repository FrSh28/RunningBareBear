#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <string>
#include "includeSDL.h"
#include "BasicObject.h"

class Layer
{
public:
	Layer(std::string _name = "", bool _active = true);
	virtual ~Layer();

	void free();							// destroy all textures and surfaces
	virtual bool handleEvents(SDL_Event &);	// handle events on current layer
	virtual void update();					// update changes on current layer
	virtual void render();					// render elements to mainTexture
	inline void setActive(bool _active) { active = _active; }

	void pushElement(BasicObject *);
	void popElement(BasicObject *);

	inline std::string getName() const { return name; }
	inline bool isActive() const { return active; }
	inline SDL_Texture *getTexture() { return mainTexture; }
	inline unsigned int getElementsSize() const { return elements.size(); }

protected:
	std::string name;
	bool active;
	bool changed;

	SDL_Texture* mainTexture;
	std::vector<BasicObject*> elements;
};

#endif	// LAYER_H
