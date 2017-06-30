#ifndef ANRI_SDL_INPUT_H
#define ANRI_SDL_INPUT_H

#include <memory>
#include <engine/input/Input.h>
#include <engine/input/InputEvent.h>
#include "SDL.h"

class SDLInput : public Input
{
    public:
        SDLInput();
        ~SDLInput();
        InputEvent getInputEventFromSDLEvent(SDL_Event *sdlEvent) override;

    private:
        SDL_Joystick* sdlJoystick;
};

#endif