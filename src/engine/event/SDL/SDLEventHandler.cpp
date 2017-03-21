#include <memory>
#include <engine/input/SDL/SDLInput.h>
#include <engine/event/EventHandler.h>
#include <engine/event/SDL/SDLEventHandler.h>

#include "SDL.h"


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
		} else if(sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP)
		{
			keyEvents.push(input->getKeyEventFromSDLEvent(&sdlEvent));
		}
	}
}

Event SDLEventHandler::getLastEventAndPop()
{
	Event eventToReturn = events.front();
	events.pop();

	return eventToReturn;
}

KeyEvent SDLEventHandler::getLastKeyEventAndPop()
{
	KeyEvent keyEventToReturn = keyEvents.front();
	keyEvents.pop();

	return keyEventToReturn;
}

bool SDLEventHandler::isEventsQueueEmpty()
{
	return events.empty();
}

bool SDLEventHandler::isKeyEventsQueueEmpty()
{
	return keyEvents.empty();
}