#ifndef ANRI_INPUT_H
#define ANRI_INPUT_H

#include "SDL.h"
#include "KeyEvent.h"

class Input 
{
    public:
        virtual ~Input();
        virtual KeyEvent getKeyEventFromSDLEvent(SDL_Event *sdlEvent) = 0;
};

#endif