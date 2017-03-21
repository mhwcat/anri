#ifndef ANRI_I_CONTROLLABLE_H
#define ANRI_I_CONTROLLABLE_H

#include <engine/input/KeyEvent.h>

class IControllable
{
	public:
		virtual ~IControllable() {};
		virtual void handleInput(KeyEvent *keyEvent) = 0;
};

#endif