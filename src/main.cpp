#include <cstdio>
#include <cstdlib>
#include <memory>

#include <game/levels/GameLevel.h>
#include <game/Game.h>
#include <engine/DebugPrint.h>
#include <engine/Config.h>

#include <engine/Allocator.h>

int main(int argc, char* args[])
{
    std::shared_ptr<MessageSystem> msgSystem = std::make_shared<MessageSystem>();
    std::unique_ptr<Game> g = std::make_unique<Game>();
    g->setMessageSystem(msgSystem);
    if(!g->init())
    {
        ANRI_DE debugPrint("Game init failed!");

        return EXIT_FAILURE;
    }

    std::unique_ptr<GameLevel> gl = std::make_unique<GameLevel>();
    std::unique_ptr<GameObject> bgObject = std::make_unique<GameObject>("bg", Vec2f{0.f, 0.f}, 1280, 720);
    gl->addGameObject(std::move(bgObject));

    gl->setPlayer(std::make_shared<PlayerGameObject>("player", Vec2f {100.f, 510.f - 121.f}, 80, 121, 0.f, 0.f, 0.f, 50.f));

    g->loadLevel(std::move(gl));

    g->start();

    ANRI_DE debugPrint("Exitting gracefully...");

    return EXIT_SUCCESS;
}


