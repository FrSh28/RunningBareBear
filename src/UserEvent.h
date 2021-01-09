#ifndef USER_EVENT
#define USER_EVENT

#include <string>
#include "includeSDL.h"

extern const unsigned int GAMESTATE_CHANGE;
extern const unsigned int CHARACTER_INTERACT;
extern const unsigned int ITEM_PICKED_UP;
extern const unsigned int ITEM_USED;
extern const unsigned int CAUGHT;

void createUserEvent(unsigned int, unsigned int, void *, void *);

#endif	// USER_EVENT