#include <game/Game.h>
#include <engine/event/EventHandler.h>
#include <engine/MemoryUsage.h>
#include <engine/render/Renderer.h>
#include <engine/DebugPrint.h>
#include <engine/Config.h>
#include <engine/DebugInfo.h>
#include <engine/Allocator.h>
#include <game/objects/ui/UiGameObject.h>
#include <string>
#include <sstream>
#include <memory>

Game::Game() : System()
{

}

Game::~Game()
{
    ANRI_DE debugPrint("Game destructor fired.");
}

bool Game::init()
{
    running = false;

    input = std::make_shared<Input>();
    input->setMessageSystem(messageSystem);

    eventHandler = std::make_unique<EventHandler>(input);
    eventHandler->setMessageSystem(messageSystem);

    renderer = std::make_unique<Renderer>();
    soundSystem = std::make_shared<SoundSystem>();
    timeElapsed = 0;
    lastRenderTime = 0.f;

    bool rendererInitialized = renderer->init();
    bool soundSystemInitialized = soundSystem->init();

    return rendererInitialized && soundSystemInitialized;
}

void Game::start() 
{
    soundSystem->loadMusic("cyberpunkAmbient", "assets/sounds/Future-Cities-ambient.ogg");
    soundSystem->loadSound("bonfire_ambient", "assets/sounds/bonfire_ambient.ogg");
    soundSystem->loadSound("bonfire_lit_sfx", "assets/sounds/bonfire_lit_sfx.ogg");
    soundSystem->loadMusic("bonfire_music", "assets/sounds/bonfire_music.ogg");
    soundSystem->playMusic("bonfire_music", 30, -1);

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
        renderer->render(currentLevel->getObjects(), currentLevel->getMovables(), currentLevel->getParticleSystems(), interp, lastRenderTime);
        lastRenderTime = frameTimer.getMicrosecondsSinceStart() / 1000.f; // micro -> milli
        ANRI_DE DebugInfo::getInstance().renderTime = lastRenderTime; 

        // Clear local allocated memory
        Allocator::getInstance().resetMemory();
    }
}

void Game::performEventHandling()
{
    eventHandler->processEvents();

    // Handle engine events
    handleEngineMessages();
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

    for(auto const& particleSystem : currentLevel->getParticleSystems())
    {
        particleSystem->update(deltaTime);
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

SDL_Renderer* Game::getMainRenderer() const 
{
    return renderer->getRenderer();
}

void Game::handleEngineMessages()
{
    while(!messageSystem->isQueueEmpty(GAME))
    {
        Message *message = messageSystem->getLastMessage(GAME);
        //debugPrint("received message %d", message);

        //debugPrint("Received message %d -> %d: %d ", message->sender, message->recipient, message->type);

        switch(message->type)
        {
            case PLAYER_MOVE:
                currentLevel->getPlayer()->move(*((float *) (message->data)), 190.f);
                break;
            case PLAYER_STOP_MOVING:
                currentLevel->getPlayer()->stopMoving();
                break;
            case PLAYER_SWITCH_TEXTURE:
                //currentLevel->getPlayer()->setTexture(*((char *) (message->data)))
                break;
            case PLAYER_WALK_LEFT:
                if(!currentLevel->getPlayer()->isInAction())
                {
                    currentLevel->getPlayer()->getTexture()->setTextureByName("player_walk", true, false);
                    currentLevel->getPlayer()->move(-180.f, 190.f);
                }
                break;
            case PLAYER_WALK_RIGHT:
                if(!currentLevel->getPlayer()->isInAction())
                {
                    currentLevel->getPlayer()->getTexture()->setTextureByName("player_walk", false, false);
                    currentLevel->getPlayer()->move(180.f, -190.f);
                }
                break;
            case PLAYER_STOP_WALKING:
                currentLevel->getPlayer()->getTexture()->setTextureByName("player_idle", currentLevel->getPlayer()->getTexture()->isFlippedHorizontal(), false);
                currentLevel->getPlayer()->stopMoving();
                break;
            case PLAYER_JUMP:
                currentLevel->getPlayer()->jump();
                break;
            case PLAYER_ATTACK:
                currentLevel->getPlayer()->getTexture()->setTextureByName("player_attack", currentLevel->getPlayer()->getTexture()->isFlippedHorizontal(), true);
                break;
            case PLAYER_ACTION:
            {
                char *actionType = (char *) message->data;
                if(strncmp(actionType, "lit_bonfire", 11) == 0 && currentLevel->getParticleSystems().empty() &&
                    currentLevel->getPlayer()->getPosition().x >= 300.f && currentLevel->getPlayer()->getPosition().x <= 500.f)
                {
                    std::unique_ptr<UiGameObject> bonfireLitTxt = std::make_unique<UiGameObject>(
                        "bonfire_lit_txt", Vec2 {180.f, 242.5f}, 600, 55);
                    bonfireLitTxt->getTexture()->loadSheet("bonfire_lit_txt", "assets/textures/bonfire_lit_txt.png", Vec2 {600.f, 55.f}, 1, 1, getMainRenderer());

                    bonfireLitTxt->show();
                    currentLevel->addGameObject(std::move(bonfireLitTxt));

                    currentLevel->getPlayer()->executeAction();

                    ParticleSystemBuilder psBuilder;
                    std::unique_ptr<ParticleSystem> ps1 = psBuilder
                        .setOriginPosition(Vec2{440.f, 495.f})
                        .setOriginSize(Vec2{20.f, 15.f})
                        .setMaxParticleCount(120)
                        .setMaxTimeRunning(1.5f)
                        .setLifespan(50.f, 200.f)
                        .applyAdditionalAcceleration(Vec2{0.f, -80.f})
                        .setVariation(Vec2{-900.f, -250.f}, Vec2{900.f, 250.f})
                        .build();

                    std::unique_ptr<ParticleSystem> ps2 = psBuilder
                        .setOriginPosition(Vec2{440.f, 495.f})
                        .setOriginSize(Vec2{10.f, 10.f})
                        .setMaxParticleCount(20)
                        .setMaxTimeRunning(0.f)
                        .setLifespan(60.f, 220.f)
                        .applyAdditionalAcceleration(Vec2{0.f, -80.f})
                        .setVariation(Vec2{-400.f, -10.f}, Vec2{400.f, 10.f})
                        .build();

                    ps1->start();
                    ps2->start();
                    currentLevel->addParticleSystem(std::move(ps1));
                    currentLevel->addParticleSystem(std::move(ps2));

                    currentLevel->getObjectByName("bonfire")->getTexture()->setTextureByName("bonfire2_lit", false, false);
                    soundSystem->playSound("bonfire_lit_sfx", 80, 0);
                    soundSystem->playSound("bonfire_ambient", 40, -1);
                }
                break;
            }
            case GAME_SHUTDOWN:
                running = false;
                break;
             default:
                 break;
        }

        // if(message->data != nullptr)
        // {
        //     free(message->data);
        // }
        //free(message);
    }
}


