#include <engine/input/Input.h>
#include <engine/messaging/MessageSystem.h>
#include <engine/Config.h>
#include <engine/DebugPrint.h>
#include <engine/Allocator.h>
#include <memory>
#include <cstring>

Input::Input() : System()
{
    ANRI_DE debugPrint("Initializing Input subsystem.");

    sdlJoystick = nullptr;
    if(Config::getInstance().getIntValueByKey("input.controllerEnabled") == 1) 
    {
        // This is somehow necessary to make gamepad work (ref: https://stackoverflow.com/questions/28105533/sdl2-joystick-dont-capture-pressed-event#comment70156193_28106190)
        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

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

    if(sdlJoystick != nullptr && SDL_JoystickGetAttached(sdlJoystick))
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
    //inputEvents.push(event);

    switch(event.type)
    {
        case SDL_KEYDOWN:
            onKeyDownEvent(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            onKeyUpEvent(event.key.keysym.sym);
            break;
        case SDL_JOYBUTTONDOWN:
            onKeyDownEvent(event.jbutton.button);
            break;
        case SDL_JOYBUTTONUP:
            onKeyUpEvent(event.jbutton.button);
            break;
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

    Message *msgMove = nullptr;

    // TODO: Make custom button mappings (Dualshocks not working)
    switch(keycode) 
    {
        case SDLK_LEFT:
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            msgMove = createMessage(AINPUT, GAME, PLAYER_WALK_LEFT);
            break;
        case SDLK_RIGHT:
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            msgMove = createMessage(AINPUT, GAME, PLAYER_WALK_RIGHT);
            break;
        case SDLK_SPACE:
        case SDL_CONTROLLER_BUTTON_A:
            msgMove = createMessage(AINPUT, GAME, PLAYER_JUMP);
            break;
        case SDLK_ESCAPE:
            msgMove = createMessage(AINPUT, GAME, GAME_SHUTDOWN);
            break;
    }    

    if(msgMove != nullptr)
    {
        //debugPrint("Posting message %d -> %d: %d", msgMove->sender, msgMove->recipient, msgMove->type);
        messageSystem->postMessage(msgMove);
    }
}

void Input::onKeyUpEvent(const SDL_Keycode& keycode) {
    releasedKeys[keycode] = true;
    heldKeys[keycode] = false;

    Message *msg = nullptr;

    switch(keycode) 
    {
        case SDLK_LEFT:
        case SDLK_RIGHT:
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            msg = createMessage(AINPUT, GAME, PLAYER_STOP_WALKING);
            break; 
    }

    if(msg != nullptr)
    {
        //debugPrint("Posting message %d -> %d: %d", msg->sender, msg->recipient, msg->type);
        messageSystem->postMessage(msg);
    }
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

void Input::handleEngineMessages()
{

}
