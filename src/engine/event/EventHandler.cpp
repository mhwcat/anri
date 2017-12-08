#include <memory>
#include <engine/event/EventHandler.h>
#include <engine/DebugPrint.h>


EventHandler::EventHandler()
{
    ANRI_DE debugPrint("Initializing EventHandler subsystem.");

    input = std::make_shared<Input>();
}

EventHandler::~EventHandler()
{
    ANRI_DE debugPrint("EventHandler destructor fired.");
}

void EventHandler::processEvents()
{
    SDL_Event sdlEvent{};

    while(SDL_PollEvent(&sdlEvent) != 0)
    {
        if(sdlEvent.type == SDL_QUIT)
        {
            Event quitEvent{};
            quitEvent.type = EventType::QUIT;

            events.push(quitEvent);
        } else if(sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP ||
                sdlEvent.type == SDL_JOYBUTTONDOWN || sdlEvent.type == SDL_JOYBUTTONUP || sdlEvent.type == SDL_JOYAXISMOTION)
        {
            inputEvents.push(input->getInputEventFromSDLEvent(&sdlEvent));
        }
    }
}

Event EventHandler::getLastEventAndPop()
{
    Event eventToReturn = events.front();
    events.pop();

    return eventToReturn;
}

InputEvent EventHandler::getLastInputEventAndPop()
{
    InputEvent inputEventToReturn = inputEvents.front();
    inputEvents.pop();

    return inputEventToReturn;
}

bool EventHandler::isEventsQueueEmpty()
{
    return events.empty();
}

bool EventHandler::isInputEventsQueueEmpty()
{
    return inputEvents.empty();
}

std::shared_ptr<Input> EventHandler::getInput()
{
    return input;
}