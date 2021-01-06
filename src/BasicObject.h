#ifndef BASICOBJECT_H
#define BASICOBJECT_H

#include <string>
#include "includeSDL.h"

class BasicObject
{
public:
	BasicObject(std::string _name = "", bool _evEn = true, bool _upEn = true, bool _rdEn = true);
	virtual ~BasicObject();

	void setEventEnable(bool _evEn);
	void setUpdateEnable(bool _upEn);
	void setRenderEnable(bool _rdEn);

	virtual bool handleEvents(SDL_Event &);	// return true if handled
	virtual void update();

	void setTexture(SDL_Texture *);
	void setRectOnScreen(SDL_Rect &);
	void setRectOnTexture(SDL_Rect &);

	inline std::string getName()  const { return name; }
	inline bool isEventEnable()  const { return eventEnable; }
	inline bool isUpdateEnable() const { return updateEnable; }
	inline bool isRenderEnable() const { return renderEnable; }
	inline SDL_Texture *getTexture() const { return texture; }
	inline const SDL_Rect *getRectOnScreen() const { return &rectOnScreen; }
	inline const SDL_Rect *getRectOnTexture() const { return &rectOnTexture; }

protected:
	std::string name;
	bool eventEnable;
	bool updateEnable;
	bool renderEnable;

	SDL_Texture *texture;
	SDL_Rect rectOnScreen;
	SDL_Rect rectOnTexture;
};

#endif	// BASICOBJECT_H
