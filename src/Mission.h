#ifndef MISSION_H
#define MISSION_H

#include <vector>
#include <string>
#include "includeSDL.h"
#include "Renderable.h"

unsigned int MISSION;

class Mission : public Renderable
{
public:
	Mission();
	~Mission();
	virtual void handleEvents(SDL_Event &) = 0;
	virtual void update() = 0;
	inline bool isSuccess() const { return success; }

protected:
	bool success;
	
};
class Mission1_1 : public Mission
{
public:
	Mission1_1();
	~Mission1_1();
	void handleEvents(SDL_Event &);
	void update();
};
class Mission1_2 : public Mission
{
public:
	Mission1_2();
	~Mission1_2();
	void handleEvents(SDL_Event &);
	void update();
};
class Mission1_3 : public Mission
{
public:
	Mission1_3();
	~Mission1_3();
	void handleEvents(SDL_Event &);
	void update();
};
class Mission2_1 : public Mission
{
public:
	Mission2_1();
	~Mission2_1();
	void handleEvents(SDL_Event &);
	void update();
};
class Mission2_2 : public Mission
{
public:
	Mission2_2();
	~Mission2_2();
	void handleEvents(SDL_Event &);
	void update();
};
class Mission2_3 : public Mission
{
public:
	Mission2_3();
	~Mission2_3();
	void handleEvents(SDL_Event &);
	void update();
};

//somewhere
//srand(time(0));
//CreateMission(rand()%MissionTotal);

enum types
{
	Mission1Type1, Mission1Type2, Mission1Type3,
	Mission2Type1, Mission2Type2, Mission2Type3,
	MissionTotal
};
Mission *CreateMission(int choice);


#endif
