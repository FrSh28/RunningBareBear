#ifndef MISSION_H
#define MISSION_H

#include <vector>
#include <string>
#include "includeSDL.h"
#include "BasicObject.h"

enum MissionTypes
{
	Mission1Type1, Mission1Type2, Mission1Type3,
	Mission2Type1, Mission2Type2, Mission2Type3,
	MissionTotal
};

class Mission : public BasicObject
{
public:
	Mission(std::string _name = "");
	~Mission();
	virtual bool handleEvents(SDL_Event &) = 0;
	virtual bool update() = 0;
	inline bool isSuccess() const { return success; }
	inline static MissionTypes &getMission() { return curMission; }
protected:
	bool success;
	static MissionTypes curMission;
	
};
class Mission1_1 : public Mission
{
public:
	Mission1_1();
	~Mission1_1();
	bool handleEvents(SDL_Event &);
	bool update();
};
class Mission1_2 : public Mission
{
public:
	Mission1_2();
	~Mission1_2();
	bool handleEvents(SDL_Event &);
	bool update();
};
class Mission1_3 : public Mission
{
public:
	Mission1_3();
	~Mission1_3();
	bool handleEvents(SDL_Event &);
	bool update();
};
class Mission2_1 : public Mission
{
public:
	Mission2_1();
	~Mission2_1();
	bool handleEvents(SDL_Event &);
	bool update();
};
class Mission2_2 : public Mission
{
public:
	Mission2_2();
	~Mission2_2();
	bool handleEvents(SDL_Event &);
	bool update();
};
class Mission2_3 : public Mission
{
public:
	Mission2_3();
	~Mission2_3();
	bool handleEvents(SDL_Event &);
	bool update();
};

//somewhere
//srand(time(0));
//CreateMission(rand()%MissionTotal);


Mission *createMission(int choice);


#endif
