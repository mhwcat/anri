#include <memory>
#include <engine/input/Input.h>
#include <engine/Config.h>
#include <engine/DebugPrint.h>

Input::Input()
{
    ANRI_DE debugPrint("Initializing Input subsystem.");

    sdlJoystick = nullptr;
    if(Config::getInstance().getIntValueByKey("input.controllerEnabled") == 1) {
        if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
        {
            ANRI_DE debugPrint("Could not initialize SDL Joystick subsystem! SDL Error: %s", SDL_GetError());
            return;
        }

        if(SDL_NumJoysticks() < 1)
        {
            ANRI_DE debugPrint("Warning: No joysticks connected!");
            return;
        }
        else
        {
            sdlJoystick = SDL_JoystickOpen(0);
            if(sdlJoystick == nullptr)
            {
                ANRI_DE debugPrint("Unable to open game controller. SDL Error: %s", SDL_GetError());
                return;
            }

            ANRI_DE debugPrint("Opened joystick %s", SDL_JoystickName(sdlJoystick));
        }
    }
}

Input::~Input()
{
    ANRI_DE debugPrint("Input destructor fired.");

    if(sdlJoystick != nullptr)
    {
        SDL_JoystickClose(sdlJoystick);
    }
}

SDL_Event Input::getLastInputEventAndPop()
{
    SDL_Event inputEventToReturn{};

    if(!inputEvents.empty()) {
        inputEventToReturn = inputEvents.front();
        inputEvents.pop();
    }

    return inputEventToReturn;
}

void Input::pushInputEvent(SDL_Event event) {
    inputEvents.push(event);

    if(event.type == SDL_KEYDOWN)
    {
        onKeyDownEvent(event.key.keysym.sym);
    } else if(event.type == SDL_KEYUP)
    {
        onKeyUpEvent(event.key.keysym.sym);
    }
}

bool Input::isInputEventsQueueEmpty()
{
    return inputEvents.empty();
}

void Input::cleanKeys() {
    // TODO: Clearing maps each frame is very wrong, make something better plz
    pressedKeys.clear();
    releasedKeys.clear();
}

void Input::onKeyDownEvent(const SDL_Keycode& keycode) {
    pressedKeys[keycode] = true;
    heldKeys[keycode] = true;
}

void Input::onKeyUpEvent(const SDL_Keycode& keycode) {
    releasedKeys[keycode] = true;
    heldKeys[keycode] = false;
}

bool Input::wasKeyPressed(SDL_Keycode keycode) {
    return pressedKeys[keycode];
}

bool Input::wasKeyReleased(SDL_Keycode keycode) {
    return releasedKeys[keycode];
}

bool Input::isKeyHeld(SDL_Keycode keycode) {
    return heldKeys[keycode];
}

Input::AnalogStickAxisValues Input::getAnalogStickAxisValues()
{
    return analogStickAxisValues;
}

