#include <memory>
#include <engine/input/SDL/SDLInput.h>
#include <engine/event/EventHandler.h>
#include <engine/event/SDL/SDLEventHandler.h>


SDLEventHandler::SDLEventHandler() : EventHandler()
{
    input = std::make_unique<SDLInput>();
}

void SDLEventHandler::processEvents()
{
    SDL_Event sdlEvent;

    while(SDL_PollEvent(&sdlEvent) != 0)
    {
        if(sdlEvent.type == SDL_QUIT)
        {
            Event quitEvent;
            quitEvent.type = EventType::QUIT;

            events.push(quitEvent);
        } else if(sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP ||
                sdlEvent.type == SDL_JOYBUTTONDOWN || sdlEvent.type == SDL_JOYBUTTONUP || sdlEvent.type == SDL_JOYAXISMOTION)
        {
            inputEvents.push(input->getInputEventFromSDLEvent(&sdlEvent));
        }
    }
}

Event SDLEventHandler::getLastEventAndPop()
{
    Event eventToReturn = events.front();
    events.pop();

    return eventToReturn;
}

InputEvent SDLEventHandler::getLastInputEventAndPop()
{
    InputEvent inputEventToReturn = inputEvents.front();
    inputEvents.pop();

    return inputEventToReturn;
}

bool SDLEventHandler::isEventsQueueEmpty()
{
    return events.empty();
}

bool SDLEventHandler::isInputEventsQueueEmpty()
{
    return inputEvents.empty();
}