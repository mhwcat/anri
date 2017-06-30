#ifndef ANRI_I_CONTROLLABLE_H
#define ANRI_I_CONTROLLABLE_H

#include "engine/input/InputEvent.h"

class IControllable
{
    public:
        virtual ~IControllable() {};
        virtual void handleInput(InputEvent *inputEvent) = 0;
};

#endif