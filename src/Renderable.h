#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <string>
#include "includeSDL.h"

class Renderable
{
public:
	Renderable(std::string _name = "");
	virtual ~Renderable();

	virtual bool handleEvents(SDL_Event &) = 0;	// return true if handled
	virtual void update() = 0;

	inline std::string getName() const { return name; }
	inline SDL_Texture *getTexture() const { return texture; }
	inline const SDL_Rect *getPosOnWindow() const { return posOnWindow; }
	inline const SDL_Rect *getPosOnTexture() const { return posOnTexture; }

protected:
	std::string name;

	SDL_Texture *texture;
	SDL_Rect* posOnWindow;
	SDL_Rect* posOnTexture;
};

#endif	// RENDERABLE_H