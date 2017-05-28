#ifndef ANRI_EVENT_HANDLER_H
#define ANRI_EVENT_HANDLER_H

#include <queue>
#include <memory>
#include <engine/event/Event.h>
#include <engine/input/KeyEvent.h>
#include <engine/input/Input.h>

class EventHandler
{
    public:
        virtual ~EventHandler();
        virtual void processEvents() = 0;
        virtual Event getLastEventAndPop() = 0;
        virtual KeyEvent getLastKeyEventAndPop() = 0;
        virtual bool isEventsQueueEmpty() = 0;
        virtual bool isKeyEventsQueueEmpty() = 0;

    protected:
        std::queue<Event> events;
        std::queue<KeyEvent> keyEvents;
        std::unique_ptr<Input> input;
};

#endif