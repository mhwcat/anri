#ifndef ANRI_INPUT_H
#define ANRI_INPUT_H

#include <engine/input/Input.h>
#include <engine/System.h>
#include <engine/messaging/Message.h>
#include <memory>
#include <map>
#include <queue>
#include "SDL.h"

class Input : public System
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

        void pushInputEvent(SDL_Event event);
        SDL_Event getLastInputEventAndPop();
        bool isInputEventsQueueEmpty();

        void cleanKeys();

        bool wasKeyPressed(SDL_Keycode keycode);
        bool wasKeyReleased(SDL_Keycode keycode);
        bool isKeyHeld(SDL_Keycode keycode);

        AnalogStickAxisValues getAnalogStickAxisValues();

        void handleEngineMessages() override;
        
    private:
        std::queue<SDL_Event> inputEvents;

        std::map<SDL_Keycode, bool> pressedKeys;
        std::map<SDL_Keycode, bool> heldKeys;
        std::map<SDL_Keycode, bool> releasedKeys;

        AnalogStickAxisValues analogStickAxisValues;
        SDL_Joystick* sdlJoystick;

        void onKeyDownEvent(const SDL_Keycode& event);
        void onKeyUpEvent(const SDL_Keycode& event);

        float getDegreesByKey(const SDL_Keycode& keycode);
};

#endif