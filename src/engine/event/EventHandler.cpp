#include <memory>
#include <engine/event/EventHandler.h>
#include <engine/DebugPrint.h>


EventHandler::EventHandler(std::shared_ptr<Input> _input)
{
    ANRI_DE debugPrint("Initializing EventHandler subsystem.");

    input = _input;
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
        } else if(isInputEvent(&sdlEvent))
        {
            input.get()->pushInputEvent(sdlEvent);
        }
    }
}

Event EventHandler::getLastEventAndPop()
{
    Event eventToReturn = events.front();
    events.pop();

    return eventToReturn;
}

bool EventHandler::isEventsQueueEmpty()
{
    return events.empty();
}

std::shared_ptr<Input> EventHandler::getInput()
{
    return input;
}

bool EventHandler::isInputEvent(SDL_Event *event) {
    return event->type == SDL_KEYDOWN || event->type == SDL_KEYUP ||
            event->type == SDL_JOYBUTTONDOWN || event->type == SDL_JOYBUTTONUP || event->type == SDL_JOYAXISMOTION;
}