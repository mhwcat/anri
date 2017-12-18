#include <string>
#include <sstream>
#include <memory>
#include <game/Game.h>
#include <engine/event/EventHandler.h>
#include <engine/MemoryUsage.h>
#include <engine/render/Renderer.h>
#include <engine/DebugPrint.h>
#include <engine/Config.h>
#include <engine/DebugInfo.h>

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
    SimpleTimer frameTimer;

    // Time between updates in microseconds
    const uint64_t dt = static_cast<const uint64_t>(Config::getInstance().getIntValueByKey("physics.updateIntervalMs") * 1000);

    uint64_t currentTime = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(Clock::now().time_since_epoch()).count());
    uint64_t accumulator = 0;
    uint64_t newTime, loopTime;
    unsigned short memoryUsageRefreshCounter = 0;

    float interp;

    while(running)
    {
        frameTimer.start();

        newTime = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(Clock::now().time_since_epoch()).count());
        loopTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += loopTime;

        // Prevent accumulator reaching too high values when updating takes too long
        if(accumulator > 250000)
            accumulator = 250000;

        // Update memory usage every fixed step
        if(memoryUsageRefreshCounter >= 1000)
        {
            ANRI_DE DebugInfo::getInstance().memoryUsageBytes = getCurrentRSS();
            memoryUsageRefreshCounter = 0;
        }
        memoryUsageRefreshCounter++;

        performEventHandling();

        while(accumulator >= dt)
        {
            update(dt / 1000000.f); // update with deltaTime in seconds
            timeElapsed += dt;
            accumulator -= dt;
        }

        // Count interpolation for rendering
        interp = (float) accumulator / (float) dt;

        ANRI_DE DebugInfo::getInstance().updateTime = frameTimer.getMicrosecondsSinceStart() / 1000.f; // micro -> milli

        frameTimer.start();
        renderer->render(currentLevel->getObjects(), currentLevel->getMovables(), interp);
        ANRI_DE DebugInfo::getInstance().renderTime = frameTimer.getMicrosecondsSinceStart() / 1000.f; // micro -> milli
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

std::shared_ptr<Input> Game::getInput()
{
    return input;
}
