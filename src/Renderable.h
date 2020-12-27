#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <string>
using namespace std;

class Renderable	// may change member funcs
{
public:
	Renderable();
	virtual ~Renderable() = 0;

	virtual void render();

	inline string getName() const { return name; }

private:
	string name;
};

#endif	// RENDERABLE_H