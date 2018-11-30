#ifndef ANRI_WORLD_H
#define ANRI_WORLD_H

#include <memory>
#include <Box2D/Box2D.h>

class World 
{
    public:
        World(World const&) = delete;
        World(World&&) = delete;

        static World& getInstance();
        std::shared_ptr<b2World> getWorld();
        
    private:
        std::shared_ptr<b2World> world;

        World();
        virtual ~World();


};

#endif