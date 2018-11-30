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

    std::unique_ptr<GameObject> groundObject = std::make_unique<GameObject>("ground", Vec2f{0.f, 700.f}, Vec2_ui32{1280, 20}, b2_staticBody, true);
    gl->addGameObject(std::move(groundObject));

    std::unique_ptr<GameObject> platformObject = std::make_unique<GameObject>("platform", Vec2f{200.f, 500.f}, Vec2_ui32{400, 20}, b2_staticBody, true);
    gl->addGameObject(std::move(platformObject));

    std::unique_ptr<MovableGameObject> movObj1 = std::make_unique<MovableGameObject>("movable1", Vec2f{20.f, 120.f}, Vec2_ui32{100, 100}, b2_dynamicBody, false, 0.f, 0.f, 0.f, 0.f);
    std::unique_ptr<MovableGameObject> movObj2 = std::make_unique<MovableGameObject>("movable2", Vec2f{700.f, 400.f}, Vec2_ui32{50, 50}, b2_dynamicBody, false, 0.f, 0.f, -0.f, 0.f);
    std::unique_ptr<MovableGameObject> movObj3 = std::make_unique<MovableGameObject>("movable3", Vec2f{346.f, 198.f}, Vec2_ui32{50, 70}, b2_dynamicBody, false, 0.f, 0.f, -0.f, 0.f);
    std::unique_ptr<MovableGameObject> movObj4 = std::make_unique<MovableGameObject>("movable4", Vec2f{930.f, 560.f}, Vec2_ui32{100, 50}, b2_dynamicBody, false, 0.f, 0.f, -0.f, 0.f);

    std::unique_ptr<MovableGameObject> movObj5 = std::make_unique<MovableGameObject>("movable5", Vec2f{200.f, 70.f}, Vec2_ui32{40, 50}, b2_dynamicBody, false, 0.f, 0.f, 0.23f, 0.f);
    std::unique_ptr<MovableGameObject> movObj6 = std::make_unique<MovableGameObject>("movable6", Vec2f{600.f, 90.f}, Vec2_ui32{20, 60}, b2_dynamicBody, false, 0.f, 0.f, -0.8f, 0.f);

    gl->addMovableGameObject(std::move(movObj1));
    gl->addMovableGameObject(std::move(movObj2));
    gl->addMovableGameObject(std::move(movObj3));
    gl->addMovableGameObject(std::move(movObj4));
    gl->addMovableGameObject(std::move(movObj5));
    gl->addMovableGameObject(std::move(movObj6));

    gl->setPlayer(std::make_shared<PlayerGameObject>("player", Vec2f {100.f, 510.f - 121.f}, Vec2_ui32{80, 121}, b2_dynamicBody, true, 0.f, 0.f, 0.f, 50.f));
    gl->getPlayer()->getGraphicsComponent()->getTexture()->loadSheet("player", "assets/sprites/player-cat.png", Vec2f{0.f, 0.f}, 1, 1, g->getMainRenderer());

    g->loadLevel(std::move(gl));

    g->start();

    ANRI_DE debugPrint("Exitting gracefully...");

    return EXIT_SUCCESS;
}


