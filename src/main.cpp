#include <cstdio>
#include <cstdlib>
#include <memory>

#include <game/Color.h>
#include <game/levels/GameLevel.h>
#include <game/Game.h>
#include <engine/DebugPrint.h>
#include <engine/Config.h>

int main(int argc, char* args[])
{
    std::unique_ptr<Game> g = std::make_unique<Game>();
    if(!g->init())
    {
        ANRI_DE debugPrint("Game init failed!");

        return EXIT_FAILURE;
    }

    std::unique_ptr<GameLevel> gl = std::make_unique<GameLevel>();
    gl->addGameObject(std::make_unique<GameObject>(0, 650, 1280, 400, Color::ColorName::GREEN, true));
    //gl->addMovableGameObject(std::make_shared<MovableGameObject>(60, 60, 15, 15, Color::ColorName::WHITE, true, 0.f, 0.f, 8.f, 8.f));
    gl->setPlayer(std::make_shared<PlayerGameObject>(100, 600, 50, 50, Color::ColorName::BLUE, true, 0.f, 0.f, 0.f, 0.f, g->getInput()));
    g->loadLevel(std::move(gl));

    g->start();

    ANRI_DE debugPrint("Exitting gracefully...");

    return EXIT_SUCCESS;
}


