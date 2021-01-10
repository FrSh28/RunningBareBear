#include <algorithm>
#include "Layer.h"
#include "Game.h"
#include "Files.h"
#include "Button.h"
#include "Timer.h"
using namespace std;

Layer::Layer(string _name, bool _active)
 : name(_name), active(_active), changed(true), mainTexture(NULL), rectViewPort({0, 0, 0, 0})
{
	Game &game = Game::GetGame();
	mainTexture = SDL_CreateTexture(game.getRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, game.getWidth(), game.getHeight());
	if(!mainTexture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture for layer %s: %s", name.c_str(), SDL_GetError());
	}
	else
	{
		SDL_SetTextureBlendMode(mainTexture, SDL_BLENDMODE_BLEND);
	}
	rectViewPort.w = game.getWidth();
	rectViewPort.h = game.getHeight();
}

Layer::~Layer()
{
	free();
}

void Layer::free()
{
	for(auto it = elements.begin(); it != elements.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
	elements.clear();
	if(mainTexture)
	{
		SDL_DestroyTexture(mainTexture);
		mainTexture = NULL;
	}
}

bool Layer::handleEvents(SDL_Event &e)
{
	for(auto it = elements.rbegin(); it != elements.rend(); ++it)
	{
		if((*it)->isEventEnable())
			if((*it)->handleEvents(e))	// if handled
			{
				changed = true;
				return true;
			}
	}
	return false;
}

void Layer::update()
{
	for(auto it = elements.begin(); it != elements.end(); ++it)
	{
		if((*it)->isUpdateEnable())
			if((*it)->update())
				changed = true;
	}
}

void Layer::render()
{
	if(changed)
	{
		SDL_Renderer *renderer = Game::GetGame().getRenderer();
		SDL_SetRenderTarget(renderer, mainTexture);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0x00);
		SDL_RenderClear(renderer);
		for(auto it = elements.begin(); it != elements.end(); ++it)
		{
			if((*it)->isRenderEnable() and (*it)->getTexture() and (*it)->getRectOnTexturePtr() and (*it)->getRectOnScreenPtr())
				SDL_RenderCopy(renderer, (*it)->getTexture(), (*it)->getRectOnTexturePtr(), (*it)->getRectOnScreenPtr());
		}
	}
	changed = false;
}

void Layer::pushElement(BasicObject *_element)
{
	elements.push_back(_element);
}

void Layer::popElement(BasicObject *_element)
{
	auto iter = find(elements.begin(), elements.begin(), _element);
	if (iter != elements.end())
	{
		elements.erase(iter);
	}
}

BackGround::BackGround(Images index, SDL_Rect _rectOnScreen)
{
	texture = loadImage(index);
	SDL_QueryTexture(texture, NULL, NULL, &rectOnTexture.w, &rectOnTexture.h);
	if(_rectOnScreen.w > 0 and _rectOnScreen.h > 0)
		rectOnScreen = _rectOnScreen;
	else
	{
		rectOnScreen.w = Game::GetGame().getWidth();
		rectOnScreen.h = Game::GetGame().getHeight();
	}
}

BackGround::~BackGround()
{}

Layer *createLayer(Layers index, BackGround *_bg)
{
	Layer *lay;
	switch(index)
	{
		case L_STARTMENU:
			lay = new Layer("StartMenu");
			if(_bg)
				lay->pushElement(_bg);
			lay->pushElement(new Button(STARTS));
			lay->pushElement(new Button(INTRO1));
			break;
		case L_STATUS:
			lay = new Layer("Status", false);
			if(_bg)
				lay->pushElement(_bg);
			lay->pushElement(new Button(PAUSES));
			lay->pushElement(new Button(MISSION));
			lay->pushElement(new Timer());
			//lay->pushElement(new backPack);
			//lay->pushElement(new strengthBar);
			break;
		case L_INTRO:
			lay = new Layer("Intro", false);
			if(_bg)
				lay->pushElement(_bg);
			lay->pushElement(new Button(LEAVEINTRO));
			break;
		case L_MISSION:
			lay = new Layer("Mission", false);
			if(_bg)
				lay->pushElement(_bg);
			lay->pushElement(new Button(LEAVEMISSION));
			break;
		case L_PAUSE:
			lay = new Layer("Pause", false);
			if(_bg)
				lay->pushElement(_bg);
			lay->pushElement(new Button(RESUMES));
			lay->pushElement(new Button(INTRO2));
			lay->pushElement(new Button(LEAVE));
			break;
		case L_END:
			lay = new Layer("End", false);
			if(_bg)
				lay->pushElement(_bg);
			lay->pushElement(new Button(OK));
			break;
		case L_LOADING:
			lay = new Layer("Loading");
			if(_bg)
				lay->pushElement(_bg);
			break;
	}
	return lay;
}
