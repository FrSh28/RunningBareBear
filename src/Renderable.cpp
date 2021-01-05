#include "Renderable.h"
using namespace std;

Renderable::Renderable(string _name)
 : name(_name), texture(NULL), posOnWindow({0, 0, 0 ,0}), posOnTexture({0, 0, 0, 0})
{}

Renderable::~Renderable()
{
	// may or may not need to destroy texture and posOnXXX
}

void Renderable::setTexture(SDL_Texture *tex)
{
	texture = tex;
}

void Renderable::setPosOnWindow(SDL_Rect &pos)
{
	posOnWindow = pos;
}

void Renderable::setPosOnTexture(SDL_Rect &pos)
{
	posOnTexture = pos;
}