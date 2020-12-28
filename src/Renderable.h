#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <string>
#include "includeSDL.h"
using namespace std;

class Renderable	// may change member funcs
{
public:
	Renderable();
	virtual ~Renderable() = 0;

	virtual bool handleEvents(SDL_Event &) = 0;	// return true if handled

	inline string getName() const { return name; }
	inline const SDL_Rect &getPosOnWindow() const { return posOnWindow;}
	inline const SDL_Rect &getPosOnTexture() const { return posOnWindow;}

protected:
	string name;

	SDL_Texture *texture;
	SDL_Rect posOnWindow;
	SDL_Rect posOnTexture;
};

#endif	// RENDERABLE_H