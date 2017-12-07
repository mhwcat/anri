#ifndef ANRI_INPUT_H
#define ANRI_INPUT_H

#include "SDL.h"
#include "InputEvent.h"

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
        virtual ~Input();
        virtual InputEvent getInputEventFromSDLEvent(SDL_Event *sdlEvent) = 0;
        virtual AnalogStickAxisValues getAnalogStickAxisValues();

    protected:
        AnalogStickAxisValues analogStickAxisValues;
};

#endif