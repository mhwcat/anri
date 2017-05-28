#ifndef ANRI_SDL_INPUT_H
#define ANRI_SDL_INPUT_H

#include <memory>
#include <engine/input/Input.h>
#include "SDL.h"

class SDLInput : public Input
{
    public:
        KeyEvent getKeyEventFromSDLEvent(SDL_Event *sdlEvent) override;
};

#endif