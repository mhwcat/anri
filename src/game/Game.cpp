#include <string>
#include <sstream>
#include <memory>
#include <game/Game.h>
#include <engine/event/SDL/SDLEventHandler.h>
#include <engine/MemoryUsage.h>
#include <engine/render/SDL/SDLRenderer.h>
#include <engine/DebugPrint.h>

Game::Game()
{
	running = false;
	eventHandler = std::make_unique<SDLEventHandler>();
	renderer = std::make_unique<SDLRenderer>();
}

Game::~Game()
{
	ANRI_DE debugPrint("Game destructor fired.");
}

bool Game::init()
{
	return renderer->init();
}

void Game::start() 
{
	running = true;
	mainLoop();
}

void Game::stop()
{
	running = false;
}

void Game::mainLoop()
{
	SimpleTimer updateTimer;

	float deltaTime = 0.f;
	while(running)
	{
		performEventHandling();

		deltaTime = (float) updateTimer.getMicrosecondsSinceStart() / 1000000.f;
		update(deltaTime);
		updateTimer.start();

		renderer->render(currentLevel->getObjects(), currentLevel->getMovables(), prepareDebugText());
	}
}

void Game::performEventHandling()
{
	eventHandler->processEvents();

	// Handle engine events
	while(!eventHandler->isEventsQueueEmpty())
	{
		Event event = eventHandler->getLastEventAndPop();
		switch(event.type)
		{
			case EventType::QUIT:
				running = false;
				break;
		}
	}

	// Handle input events
	while(!eventHandler->isKeyEventsQueueEmpty())
	{
		KeyEvent keyEvent = eventHandler->getLastKeyEventAndPop();

		currentLevel->getPlayer()->handleInput(&keyEvent);
	}
}

void Game::update(float deltaTime)
{
	for(auto const& movable : currentLevel->getMovables()) 
	{
		if(movable->hasCollisionEnabled())
		{
			bool collisionDetected = false;

			for(auto const& checkedMovable : currentLevel->getMovables())
			{
				if(movable != checkedMovable)
				{
					collisionDetected = (movable->getX() < checkedMovable->getX() + checkedMovable->getWidth()) &&
										(movable->getX() + movable->getWidth() > checkedMovable->getX()) &&
										(movable->getY() < checkedMovable->getY() + checkedMovable->getHeight()) &&
										(movable->getHeight() + movable->getY() > checkedMovable->getY());

					if(collisionDetected && !movable->isColliding())
					{
						ANRI_DE debugPrint("%d entered collision with %d", movable->getId(), checkedMovable->getId());
						movable->setColliding(true);
						break;
					} else if(!collisionDetected && movable->isColliding())
					{
						ANRI_DE debugPrint("%d exited collision", movable->getId());
						movable->setColliding(false);
					}
				}
			}

//			if(!collisionDetected) {
				movable->move(deltaTime);
//			}
		} else {
			movable->move(deltaTime);
		}
	}
}

void Game::loadLevel(std::unique_ptr<GameLevel> level)
{
	currentLevel = std::move(level);
}

std::string Game::prepareDebugText()
{
	std::stringstream ss;
	ss.precision(4);

	ss << "MEM: " << getCurrentRSS() / 1024.f / 1024.f << " MB" << std::endl;
	ss << "Object count: " << (currentLevel->getObjects().size() + currentLevel->getMovables().size());

	return ss.str();
}
