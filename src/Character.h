#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "includeSDL.h"
#include "BasicObject.h"

class Character : public BasicObject
{
public:
	Character(std::string _name = "") : BasicObject(_name)
	{}
	virtual ~Character(){}

	virtual SDL_Point getPixelPos() const { return SDL_Point({0, 0});}
	
};

#endif	// CHARACTER_H