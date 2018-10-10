#include <vector>
#include <memory>
#include <game/levels/GameLevel.h>
#include <engine/DebugPrint.h>

GameLevel::GameLevel()
{
    lastId = 0;
}

GameLevel::~GameLevel() 
{
    ANRI_DE debugPrint("Game level destructor fired.");
}

const std::vector<std::unique_ptr<GameObject> >& GameLevel::getObjects() const
{
    return objects;
}

const std::vector<std::shared_ptr<MovableGameObject> >& GameLevel::getMovables() const
{
    return movables;
}

const std::shared_ptr<PlayerGameObject>& GameLevel::getPlayer() const
{
    return player;
}

const std::vector<std::unique_ptr<ParticleSystem> >& GameLevel::getParticleSystems() const
{
    return particleSystems;
}

void GameLevel::setPlayer(std::shared_ptr<PlayerGameObject> playerGameObject)
{
    player = std::move(playerGameObject);
    addMovableGameObject(player);
}

void GameLevel::addGameObject(std::unique_ptr<GameObject> gameObject)
{
    gameObject->setId(++lastId);

    ANRI_DE debugPrint("GameObject[%d] added to level.", gameObject->getId());
    objects.push_back(std::move(gameObject));
}

void GameLevel::addMovableGameObject(std::shared_ptr<MovableGameObject> movableGameObject)
{
    movableGameObject->setId(++lastId);

    ANRI_DE debugPrint("MovableGameObject[%d] added to level.", movableGameObject->getId());
    movables.push_back(std::move(movableGameObject));
}

void GameLevel::addParticleSystem(std::unique_ptr<ParticleSystem> particleSystem)
{
    ANRI_DE debugPrint("ParticleSystem[] added to level.");
    particleSystems.push_back(std::move(particleSystem));
}

const std::unique_ptr<GameObject>& GameLevel::getGameObject(uint32_t id) const
{
    for(auto const& go : objects)
    {
        if(go->getId() == id)
            return go;
    }

    ANRI_DE debugPrint("GameObject[%d] not found!", id);
    static std::unique_ptr<GameObject> gameObjectNotFound;
    return gameObjectNotFound;
}

const std::unique_ptr<GameObject>& GameLevel::getObjectByName(std::string name) const
{
    for(auto const& go : objects)
    {
        if(go->getName().compare(name) == 0)
            return go;
    }

    ANRI_DE debugPrint("GameObject[%s] not found!", name);
    static std::unique_ptr<GameObject> gameObjectNotFound;
    return gameObjectNotFound;
}

void GameLevel::removeGameObject(uint32_t id)
{
    std::vector<std::unique_ptr<GameObject> >::iterator it;
    std::vector<std::unique_ptr<GameObject> >::iterator position;

    for(it = objects.begin(); it != objects.end(); it++)
    {
        if((*it)->getId() == id)
        {
            position = it;
            break;
        }
    }

    if(it == objects.end())
    {
        ANRI_DE debugPrint("GameObject[%d] was not found to remove!", id);
        return;
    }

    objects.erase(position);
    ANRI_DE debugPrint("GameObject[%d] removed from level.", id);
}

