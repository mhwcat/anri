#include <memory>
#include <engine/input/SDL/SDLInput.h>
#include <engine/Config.h>
#include <engine/DebugPrint.h>

SDLInput::SDLInput()
{
    if(Config::getInstance().getIntValueByKey("input.controllerEnabled") == 1) {
        sdlJoystick = nullptr;

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

SDLInput::~SDLInput()
{
    if(sdlJoystick != nullptr)
    {
        SDL_JoystickClose(sdlJoystick);
    }
}

/**
 * TODO:
 * Fix mappings for DS4 controller (DPAD not working), check mappings for X360 controller
 */
InputEvent SDLInput::getInputEventFromSDLEvent(SDL_Event *sdlEvent)
{
    InputEvent keyEvent;

    if(Config::getInstance().getIntValueByKey("input.controllerEnabled"))
    {
        if(sdlEvent->type == SDL_JOYAXISMOTION)
        {
            if(sdlEvent->jaxis.axis == 0) // lstick X
                analogStickAxisValues.lStickX = sdlEvent->jaxis.value;
            if(sdlEvent->jaxis.axis == 1) // lstick Y
                analogStickAxisValues.lStickY = sdlEvent->jaxis.value;
        }
    }

    switch(sdlEvent->type)
    {
        case SDL_KEYDOWN:
            keyEvent.type = InputEventType::KB_KEY_DOWN;
            break;
        case SDL_KEYUP:
            keyEvent.type = InputEventType::KB_KEY_UP;
            break;
        case SDL_JOYBUTTONDOWN:
            keyEvent.type = InputEventType::PAD_BUTTON_DOWN;
            break;
        case SDL_JOYBUTTONUP:
            keyEvent.type = InputEventType::PAD_BUTTON_UP;
            break;
        default:
            keyEvent.type = InputEventType::INPUT_EVENT_UNKNOWN;
    }

    if(sdlEvent->type == SDL_KEYDOWN || sdlEvent->type == SDL_KEYUP)
    {
        switch(sdlEvent->key.keysym.sym)
        {
            case SDLK_UP:
                keyEvent.value = InputValue::KB_ARROW_UP;
                break;
            case SDLK_DOWN:
                keyEvent.value = InputValue::KB_ARROW_DOWN;
                break;
            case SDLK_LEFT:
                keyEvent.value = InputValue::KB_ARROW_LEFT;
                break;
            case SDLK_RIGHT:
                keyEvent.value = InputValue::KB_ARROW_RIGHT;
                break;
            case SDLK_SPACE:
                keyEvent.value = InputValue::KB_SPACE;
                break;
            case SDLK_RETURN:
                keyEvent.value = InputValue::KB_ENTER;
                break;
            default:
                keyEvent.value = InputValue::INPUT_VALUE_UNKNOWN;
                break;
        }
    } else if(sdlEvent->type == SDL_JOYBUTTONDOWN || sdlEvent->type == SDL_JOYBUTTONUP)
    {
        switch(sdlEvent->jbutton.button) {
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                keyEvent.value = InputValue::PAD_DPAD_UP;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                keyEvent.value = InputValue::PAD_DPAD_DOWN;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                keyEvent.value = InputValue::PAD_DPAD_LEFT;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                keyEvent.value = InputValue::PAD_DPAD_RIGHT;
                break;
            case SDL_CONTROLLER_BUTTON_A:
                keyEvent.value = InputValue::PAD_A;
                break;
            case SDL_CONTROLLER_BUTTON_B:
                keyEvent.value = InputValue::PAD_B;
                break;
            case SDL_CONTROLLER_BUTTON_X:
                keyEvent.value = InputValue::PAD_X;
                break;
            case SDL_CONTROLLER_BUTTON_Y:
                keyEvent.value = InputValue::PAD_Y;
                break;
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                keyEvent.value = InputValue::PAD_RIGHT_BUTTON;
                break;
            case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                keyEvent.value = InputValue::PAD_LEFT_BUTTON;
                break;
            case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
                keyEvent.value = InputValue::PAD_RIGHT_STICK;
                break;
            case SDL_CONTROLLER_BUTTON_LEFTSTICK:
                keyEvent.value = InputValue::PAD_LEFT_STICK;
                break;
            case SDL_CONTROLLER_BUTTON_START:
                keyEvent.value = InputValue::PAD_START;
                break;
            case SDL_CONTROLLER_BUTTON_BACK:
                keyEvent.value = InputValue::PAD_BACK;
                break;
            default:
                keyEvent.value = InputValue::INPUT_VALUE_UNKNOWN;
                break;
        }
    }

    return keyEvent;
}