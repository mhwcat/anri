#include <cstdio>
#include <cstdlib>
#include <memory>

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
    std::unique_ptr<GameObject> bgObject = std::make_unique<GameObject>(Vec2 {0.f, 0.f}, 1280, 720, false);
    bgObject->getTexture()->loadSheet("tex_bg", "assets/textures/background.png", Vec2 {0, 0}, 0, g->getMainRenderer());
    gl->addGameObject(std::move(bgObject));

    gl->setPlayer(std::make_shared<PlayerGameObject>(Vec2 {100.f, 100.f}, 80, 121, true, 0.f, 0.f, 0.f, 50.f, g->getInput()));
    gl->getPlayer()->getTexture()->loadSheet("player_idle", "assets/textures/mr_skeleton_idle.png", Vec2 {91, 0}, 11, g->getMainRenderer());
    gl->getPlayer()->getTexture()->loadSheet("player_walk", "assets/textures/mr_skeleton_walk.png", Vec2 {81, 0}, 13, g->getMainRenderer());

    gl->getPlayer()->getTexture()->setTexture("player_idle", false);

    g->loadLevel(std::move(gl));

    g->start();

    ANRI_DE debugPrint("Exitting gracefully...");

    return EXIT_SUCCESS;
}


