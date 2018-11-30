#include <engine/physics/World.h>
#include <engine/DebugPrint.h>

World::World()
{
    b2Vec2 gravity(0, 59.8f);

    world = std::make_shared<b2World>(gravity);
}

World::~World()
{
    ANRI_DE debugPrint("World destructor fired.");
}

World& World::getInstance()
{
    static World instance;

    return instance;
}

std::shared_ptr<b2World> World::getWorld()
{
    return world;
}