#ifndef ANRI_EVENT_HANDLER_H
#define ANRI_EVENT_HANDLER_H

#include <engine/event/EventHandler.h>
#include <engine/event/Event.h>
#include <engine/input/Input.h>
#include <engine/System.h>
#include <queue>

class EventHandler : public System
{
    public:
        EventHandler(std::shared_ptr<Input> _input);
        virtual ~EventHandler();

        void processEvents();
        Event getLastEventAndPop();
        bool isEventsQueueEmpty();

        std::shared_ptr<Input> getInput();

    private:
        std::queue<Event> events;
        std::shared_ptr<Input> input;

        bool isInputEvent(SDL_Event *event);

        void handleEngineMessages() override;
};

#endif