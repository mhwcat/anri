#ifndef ANRI_EVENT_HANDLER_H
#define ANRI_EVENT_HANDLER_H

#include <queue>
#include <memory>
#include <engine/event/Event.h>
#include <engine/input/Input.h>
#include <engine/input/InputEvent.h>

class EventHandler
{
    public:
        EventHandler();
        virtual ~EventHandler();
        virtual void processEvents() = 0;
        virtual Event getLastEventAndPop() = 0;
        virtual InputEvent getLastInputEventAndPop() = 0;
        virtual bool isEventsQueueEmpty() = 0;
        virtual bool isInputEventsQueueEmpty() = 0;

    protected:
        std::queue<Event> events;
        std::queue<InputEvent> inputEvents;
        std::unique_ptr<Input> input;
};

#endif