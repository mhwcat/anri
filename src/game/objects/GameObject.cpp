#include <cmath>
#include <cstdint>
#include <memory>
#include <game/objects/GameObject.h>
#include <engine/DebugPrint.h>


GameObject::GameObject(std::string _name, Vec2f _position, Vec2_ui32 _size, b2BodyType _bodyType, bool _fixedRotation)
{
    name = _name;
    size = _size;
    type = GameObjectType::GAME_OBJECT;

    physicsComponent = std::make_shared<PhysicsComponent>(_name, _position, _size, _bodyType, _fixedRotation);
    graphicsComponent = std::make_shared<GraphicsComponent>(name, physicsComponent);
}

GameObject::~GameObject()
{
    ANRI_DE debugPrint("GameObject[%d] destructor fired.", id);
}

void GameObject::update(float deltaTime)
{

}

uint32_t GameObject::getId() const
{
    return id;
}

void GameObject::setId(uint32_t _id)
{
    id = _id;
}

std::string GameObject::getName() const
{
    return name;
}

std::shared_ptr<GraphicsComponent> GameObject::getGraphicsComponent()
{
    return graphicsComponent;
}

std::shared_ptr<PhysicsComponent> GameObject::getPhysicsComponent()
{
    return physicsComponent;
}

Vec2_ui32 GameObject::getSize() const
{
    return size;
}

GameObjectType GameObject::getType() const
{
    return type;
}

bool GameObject::operator==(const GameObject &rhs) const
{
    return id == rhs.id;
}

bool GameObject::operator!=(const GameObject &rhs) const
{
    return id != rhs.id;
}