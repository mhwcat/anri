#include <cstdio>
#include <cstdlib>
#include <memory>

#include <game/levels/GameLevel.h>
#include <game/Game.h>
#include <engine/DebugPrint.h>
#include <engine/Config.h>
#include <engine/Allocator.h>
#include <Box2D/Box2D.h>

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
    std::unique_ptr<GameObject> bgObject = std::make_unique<GameObject>("bg", Vec2f{0.f, 0.f}, Vec2_ui32{1280, 720});
    gl->addGameObject(std::move(bgObject));

    std::unique_ptr<MovableGameObject> movObj1 = std::make_unique<MovableGameObject>("movable1", Vec2f{500.f, 100.f}, Vec2_ui32{100, 100}, 25.f, 0.f, 100.f, 0.f);
    std::unique_ptr<MovableGameObject> movObj2 = std::make_unique<MovableGameObject>("movable2", Vec2f{700.f, 100.f}, Vec2_ui32{100, 100}, -25.f, 0.f, -100.f, 0.f);
    gl->addMovableGameObject(std::move(movObj1));
    gl->addMovableGameObject(std::move(movObj2));

    gl->setPlayer(std::make_shared<PlayerGameObject>("player", Vec2f {100.f, 510.f - 121.f}, Vec2_ui32{80, 121}, 0.f, 0.f, 0.f, 50.f));
    gl->getPlayer()->getGraphicsComponent()->getTexture()->loadSheet("player", "assets/sprites/player-cat.png", Vec2f{0.f, 0.f}, 1, 1, g->getMainRenderer());

    g->loadLevel(std::move(gl));

    g->start();

    ANRI_DE debugPrint("Exitting gracefully...");

    return EXIT_SUCCESS;
}


