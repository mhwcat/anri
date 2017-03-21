#include <memory>
#include <engine/input/SDL/SDLInput.h>
#include "SDL.h"

KeyEvent SDLInput::getKeyEventFromSDLEvent(SDL_Event *sdlEvent)
{
    KeyEvent keyEvent;

    if(sdlEvent->type == SDL_KEYDOWN)
        keyEvent.type = KeyEventType::KEY_DOWN;
    if(sdlEvent->type == SDL_KEYUP)
        keyEvent.type = KeyEventType::KEY_UP;

    switch(sdlEvent->key.keysym.sym)
    {
        case SDLK_UP:
            keyEvent.value = KeyValue::ARROW_UP;
            break;
        case SDLK_DOWN:
            keyEvent.value = KeyValue::ARROW_DOWN;
            break;
        case SDLK_LEFT:
            keyEvent.value = KeyValue::ARROW_LEFT;
            break;
        case SDLK_RIGHT:
            keyEvent.value = KeyValue::ARROW_RIGHT;
            break;
        case SDLK_SPACE:
            keyEvent.value = KeyValue::SPACE;
            break;
        case SDLK_RETURN:
            keyEvent.value = KeyValue::ENTER;
            break;
        default:
            keyEvent.value = KeyValue::ENTER;
            break;
    }

    return keyEvent;
}

