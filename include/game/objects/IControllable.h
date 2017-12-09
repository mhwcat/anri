#ifndef ANRI_I_CONTROLLABLE_H
#define ANRI_I_CONTROLLABLE_H

#include "SDL_events.h"

class IControllable
{
    public:
        virtual ~IControllable() {};
        virtual void handleInput() = 0;
};

#endif