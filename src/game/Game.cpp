#include <string>
#include <sstream>
#include <memory>
#include <game/Game.h>
#include <engine/event/EventHandler.h>
#include <engine/MemoryUsage.h>
#include <engine/render/Renderer.h>
#include <engine/DebugPrint.h>
#include <engine/Config.h>

Game::Game()
{
    running = false;
    input = std::make_shared<Input>();
    eventHandler = std::make_unique<EventHandler>(input);
    renderer = std::make_unique<Renderer>();
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
}

void Game::update(float deltaTime)
{
    for(auto const& go : currentLevel->getObjects())
    {
        go->update(deltaTime);
    }

    for(auto const& movable : currentLevel->getMovables()) 
    {
        movable->update(deltaTime);
    }

    input.get()->cleanKeys();
    currentLevel->getPlayer()->update(deltaTime);
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
    ss << "Object count: " << (currentLevel->getObjects().size() + currentLevel->getMovables().size()) << std::endl;
    if(Config::getInstance().getIntValueByKey("input.controllerEnabled") == 1)
    {
        ss << "Controller X: " << eventHandler->getInput()->getAnalogStickAxisValues().lStickX;
    }


    return ss.str();
}

std::shared_ptr<Input> Game::getInput()
{
    return input;
}
