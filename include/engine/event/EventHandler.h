#ifndef ANRI_EVENT_HANDLER_H
#define ANRI_EVENT_HANDLER_H

#include <engine/event/EventHandler.h>
#include <engine/event/Event.h>
#include <engine/input/InputEvent.h>
#include <engine/input/Input.h>
#include <queue>

class EventHandler
{
    public:
        EventHandler();
        virtual ~EventHandler();

        void processEvents();
        Event getLastEventAndPop();
        InputEvent getLastInputEventAndPop();
        bool isEventsQueueEmpty();
        bool isInputEventsQueueEmpty();

        std::shared_ptr<Input> getInput();

    private:
        std::queue<Event> events;
        std::queue<InputEvent> inputEvents;
        std::shared_ptr<Input> input;

};

#endif