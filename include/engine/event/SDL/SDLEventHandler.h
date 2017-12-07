#ifndef ANRI_SDL_EVENT_HANDLER_H
#define ANRI_SDL_EVENT_HANDLER_H

#include <engine/event/EventHandler.h>
#include <engine/event/Event.h>

class SDLEventHandler : public EventHandler
{
    public:
        SDLEventHandler();

        void processEvents() override;
        Event getLastEventAndPop() override;
        InputEvent getLastInputEventAndPop() override;
        bool isEventsQueueEmpty() override;
        bool isInputEventsQueueEmpty() override;

        std::shared_ptr<Input> getInput() override;
};

#endif