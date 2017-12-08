#ifndef ANRI_INPUT_H
#define ANRI_INPUT_H

#include <memory>
#include <engine/input/Input.h>
#include <engine/input/InputEvent.h>
#include "SDL.h"

class Input
{
    public:
        struct AnalogStickAxisValues
        {
            int16_t lStickX;
            int16_t lStickY;
            int16_t rStickX;
            int16_t rStickY;
        };

        Input();
        ~Input();
        InputEvent getInputEventFromSDLEvent(SDL_Event *sdlEvent);
        AnalogStickAxisValues getAnalogStickAxisValues();

    private:
        AnalogStickAxisValues analogStickAxisValues;
        SDL_Joystick* sdlJoystick;
};

#endif