#ifndef ANRI_INPUT_H
#define ANRI_INPUT_H

#include "SDL.h"
#include "InputEvent.h"

class Input 
{
    public:
        Input();
        virtual ~Input();
        virtual InputEvent getInputEventFromSDLEvent(SDL_Event *sdlEvent) = 0;
};

#endif