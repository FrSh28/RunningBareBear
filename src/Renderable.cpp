#include <string>
#include "includeSDL.h"
#include "Renderable.h"
using namespace std;

Renderable::Renderable(string _name)
 : name(_name), texture(NULL), posOnWindow(NULL), posOnTexture(NULL)
{}

Renderable::~Renderable()
{}
