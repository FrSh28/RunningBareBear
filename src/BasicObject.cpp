#include "BasicObject.h"
using namespace std;

BasicObject::BasicObject(string _name)
 : name(_name), texture(NULL), posOnWindow({0, 0, 0 ,0}), posOnTexture({0, 0, 0, 0})
{}

BasicObject::~BasicObject()
{
	// may or may not need to destroy texture and posOnXXX
}

void BasicObject::setTexture(SDL_Texture *tex)
{
	texture = tex;
}

void BasicObject::setPosOnWindow(SDL_Rect &pos)
{
	posOnWindow = pos;
}

void BasicObject::setPosOnTexture(SDL_Rect &pos)
{
	posOnTexture = pos;
}