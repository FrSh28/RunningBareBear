#include "BasicObject.h"
using namespace std;

BasicObject::BasicObject(string _name, bool _evEn, bool _upEn, bool _rdEn)
 : name(_name), eventEnable(_evEn), updateEnable(_upEn), renderEnable(_rdEn),
   texture(NULL), rectOnScreen({0, 0, 0 ,0}), rectOnTexture({0, 0, 0, 0})
{}

BasicObject::~BasicObject()
{}

void BasicObject::setEventEnable(bool _evEn)
{ eventEnable = _evEn; }

void BasicObject::setUpdateEnable(bool _upEn)
{ updateEnable = _upEn; }

void BasicObject::setRenderEnable(bool _rdEn)
{ renderEnable = _rdEn; }

bool BasicObject::handleEvents(SDL_Event &)	// return true if handled
{ return false; }

void BasicObject::update()
{}

void BasicObject::setTexture(SDL_Texture *tex)
{ texture = tex; }

void BasicObject::setRectOnScreen(SDL_Rect &rect)
{ rectOnScreen = rect; }

void BasicObject::setRectOnTexture(SDL_Rect &rect)
{ rectOnTexture = rect; }
