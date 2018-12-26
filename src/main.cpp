#include <cstdio>
#include <cstdlib>
#include <memory>

#include <game/levels/GameLevel.h>
#include <game/Game.h>
#include <engine/DebugPrint.h>
#include <engine/Config.h>
#include <engine/Allocator.h>
#include <engine/resource/TextureResourceManager.h>
#include <engine/resource/SoundResourceManager.h>
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

    TextureResourceManager::getInstance()->add("block-tex", "assets/sprites/block.png", g->getMainRenderer());
    TextureResourceManager::getInstance()->add("player-block-tex", "assets/sprites/player-block.png", g->getMainRenderer());

    std::unique_ptr<GameObject> blockObject = std::make_unique<GameObject>("block", Vec2f{200.f, 200.f}, Vec2_ui32{80, 50}, b2_staticBody, true);
    blockObject->getGraphicsComponent()->getTexture()->loadSheet("block", "block-tex", Vec2f{0.f, 0.f}, 1, 1);
    gl->addGameObject(std::move(blockObject));

    gl->setPlayer(std::make_shared<PlayerGameObject>("player", Vec2f {300.f, 500.f}, Vec2_ui32{74, 24}, b2_dynamicBody, true, 0.f, 0.f, 0.f, 0.f));
    gl->getPlayer()->getGraphicsComponent()->getTexture()->loadSheet("block", "player-block-tex", Vec2f{0.f, 0.f}, 1, 1);
    g->loadLevel(std::move(gl));

    g->start();

    ANRI_DE debugPrint("Exitting gracefully...");

    return EXIT_SUCCESS;
}


