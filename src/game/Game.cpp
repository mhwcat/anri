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
    timeElapsed = 0;
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
    typedef std::chrono::high_resolution_clock Clock;

    // Time between updates in microseconds
    const uint64_t dt = static_cast<const uint64_t>(Config::getInstance().getIntValueByKey("physics.updateIntervalMs") * 1000);

    uint64_t currentTime = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(Clock::now().time_since_epoch()).count());
    uint64_t accumulator = 0;
    uint64_t newTime, loopTime;

    float interp;

    while(running)
    {
        newTime = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(Clock::now().time_since_epoch()).count());
        loopTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += loopTime;

        // Prevent accumulator reaching too high values when updating takes too long
        if(accumulator > 250000)
            accumulator = 250000;

        performEventHandling();

        while(accumulator >= dt)
        {
            update(dt / 1000000.f); // update with deltaTime in seconds
            timeElapsed += dt;
            accumulator -= dt;
        }

        // Count interpolation for rendering
        interp = (float) accumulator / (float) dt;

        renderer->render(currentLevel->getObjects(), currentLevel->getMovables(), prepareDebugText(), interp);
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

    ss << "MEM: " << getCurrentRSS() / 1024.f / 1024.f << " MB" << "\n";
    ss << "Object count: " << (currentLevel->getObjects().size() + currentLevel->getMovables().size()) << "\n";
    ss << "Player pos:\nX = " << currentLevel->getPlayer()->getPosition().x << "\nY = " << currentLevel->getPlayer()->getPosition().y << "\n";
    ss << "Player vel:\nX = " << currentLevel->getPlayer()->getXVelocity() << "\nY = " << currentLevel->getPlayer()->getYVelocity();

    return ss.str();
}

std::shared_ptr<Input> Game::getInput()
{
    return input;
}
