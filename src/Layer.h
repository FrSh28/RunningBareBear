#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <string>
#include "includeSDL.h"
#include "BasicObject.h"

enum Layers
{
	L_STARTMENU,
	L_STATUS,
	L_INTRO,
	L_MISSION,
	L_PAUSE,
	L_END,
	L_LOADING,
};
//L_MAP_GROUND,
//L_MAP_FRONT,
//L_CHARACTER,

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
	inline void setRectViewPs(SDL_Point &_pos) { rectViewPort.x = _pos.x; rectViewPort.y = _pos.y; }

	void pushElement(BasicObject *);
	void popElement(BasicObject *);

	inline std::string getName() const { return name; }
	inline bool isActive() const { return active; }
	inline SDL_Texture *getTexture() { return mainTexture; }
	inline SDL_Rect *getRectViewPort() { return &rectViewPort; }
	inline unsigned int getElementsSize() const { return elements.size(); }

protected:
	std::string name;
	bool active;
	bool changed;

	SDL_Texture* mainTexture;
	SDL_Rect rectViewPort;
	std::vector<BasicObject*> elements;
};

Layer *createLayer(Layers index, BasicObject *background = NULL);

#endif	// LAYER_H
