#ifndef USER_EVENT
#define USER_EVENT

#include <string>
#include "includeSDL.h"

extern unsigned int GAMESTATE_CHANGE;
extern unsigned int CHARACTER_INTERACT;
extern unsigned int ITEM_PICKED_UP;
extern unsigned int ITEM_USED;
extern unsigned int CAUGHT;

void createUserEvent(unsigned int, unsigned int, void *, void *);

#endif	// USER_EVENT