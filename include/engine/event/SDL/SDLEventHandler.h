#ifndef ANRI_SDL_EVENT_HANDLER_H
#define ANRI_SDL_EVENT_HANDLER_H

#include <engine/event/EventHandler.h>
#include <engine/event/Event.h>
#include <engine/input/KeyEvent.h>

class SDLEventHandler : public EventHandler
{
    public:
        SDLEventHandler();

        void processEvents() override;
        Event getLastEventAndPop() override;
        KeyEvent getLastKeyEventAndPop() override;
        bool isEventsQueueEmpty() override;
        bool isKeyEventsQueueEmpty() override;
};

#endif