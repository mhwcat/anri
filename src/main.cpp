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
    std::unique_ptr<GameObject> bgObject = std::make_unique<GameObject>(Vec2 {0.f, 0.f}, 1280, 720, false);
    bgObject->getTexture()->loadSheet("tex_bg", "assets/textures/background.png", Vec2 {0, 0}, 0, g->getMainRenderer());
    gl->addGameObject(std::move(bgObject));

    std::unique_ptr<GameObject> bonfireObject = std::make_unique<GameObject>(Vec2 {830.f, 668.f - 60.f}, 60, 60, false);
    bonfireObject->getTexture()->loadSheet("bonfire_lit", "assets/textures/bonfire_lit.png", Vec2 {60, 0}, 9, g->getMainRenderer());
    bonfireObject->getTexture()->loadSheet("bonfire_kindle", "assets/textures/bonfire_kindle.png", Vec2 {60, 0}, 9, g->getMainRenderer());
    bonfireObject->getTexture()->setTexture("bonfire_lit", false);
    gl->addGameObject(std::move(bonfireObject));

    gl->setPlayer(std::make_shared<PlayerGameObject>(Vec2 {100.f, 100.f}, 80, 121, true, 0.f, 0.f, 0.f, 50.f, g->getInput()));
    gl->getPlayer()->getTexture()->loadSheet("player_idle", "assets/textures/mr_skeleton_idle.png", Vec2 {91, 0}, 11, g->getMainRenderer());
    gl->getPlayer()->getTexture()->loadSheet("player_walk", "assets/textures/mr_skeleton_walk.png", Vec2 {81, 0}, 13, g->getMainRenderer());
    gl->getPlayer()->getTexture()->setTexture("player_idle", false);

    std::unique_ptr<ParticleSystem> ps1 = std::make_unique<ParticleSystem>(Vec2{350.f, 150.f}, 30, 10.f, 100.f, false);
    ps1->start();
    gl->addParticleSystem(std::move(ps1));
    std::unique_ptr<ParticleSystem> ps2 = std::make_unique<ParticleSystem>(Vec2{650.f, 150.f}, 30, 10.f, 100.f, true);
    ps2->start();
    gl->addParticleSystem(std::move(ps2));
    
    g->loadLevel(std::move(gl));

    g->start();

    ANRI_DE debugPrint("Exitting gracefully...");

    return EXIT_SUCCESS;
}


