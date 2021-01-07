#include "BasicObject.h"
using namespace std;

BasicObject::BasicObject(string _name, bool _evEn, bool _upEn, bool _rdEn)
 : name(_name), eventEnable(_evEn), updateEnable(_upEn), renderEnable(_rdEn),
   texture(NULL), rectOnScreen({0, 0, 0 ,0}), rectOnTexture({0, 0, 0, 0})
{}

BasicObject::~BasicObject()
{}

bool BasicObject::handleEvents(SDL_Event &event)	// return true if handled
{ return false; }

bool BasicObject::update()
{ return false; }
