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
    std::unique_ptr<GameObject> bgObject = std::make_unique<GameObject>("bg", Vec2{0.f, 0.f}, 960, 540, false);
    bgObject->getTexture()->loadSheet("background2", "assets/textures/background2.png", Vec2{960.f, 540.f}, 4, 22, g->getMainRenderer());
    bgObject->getTexture()->setTextureByName("background2", false, false);
    gl->addGameObject(std::move(bgObject));

    std::unique_ptr<GameObject> bonfireObject = std::make_unique<GameObject>("bonfire", Vec2 {361.f, 373.f}, 154, 146, false);
    bonfireObject->getTexture()->loadSheet("bonfire2_normal", "assets/textures/bonfire2_normal.png", Vec2 {154.f, 146.f}, 1, 1, g->getMainRenderer());
    bonfireObject->getTexture()->loadSheet("bonfire2_lit", "assets/textures/bonfire2_lit.png", Vec2 {154.f, 146.f}, 12, 12, g->getMainRenderer());
    bonfireObject->getTexture()->setTextureByName("bonfire2_normal", false, false);
    gl->addGameObject(std::move(bonfireObject));

    gl->setPlayer(std::make_shared<PlayerGameObject>("player", Vec2 {100.f, 510.f - 121.f}, 80, 121, true, 0.f, 0.f, 0.f, 50.f, g->getInput()));
    gl->getPlayer()->getTexture()->loadSheet("player_idle", "assets/textures/mr_skeleton_idle.png", Vec2 {91, 0}, 11, 11, g->getMainRenderer());
    gl->getPlayer()->getTexture()->loadSheet("player_walk", "assets/textures/mr_skeleton_walk.png", Vec2 {81, 0}, 13, 13, g->getMainRenderer());
    gl->getPlayer()->getTexture()->loadSheet("player_attack", "assets/textures/mr_skeleton_attack.png", Vec2 {140, 0}, 18, 18, g->getMainRenderer());
    gl->getPlayer()->getTexture()->loadSheet("player_action", "assets/textures/mr_skeleton_action.png", Vec2 {81, 0}, 14, 14, g->getMainRenderer());
    gl->getPlayer()->getTexture()->setTextureByName("player_idle", false, false);

    g->loadLevel(std::move(gl));

    g->start();

    ANRI_DE debugPrint("Exitting gracefully...");

    return EXIT_SUCCESS;
}


