#include <cmath>
#include <cstdint>
#include <memory>
#include <game/objects/GameObject.h>
#include <engine/DebugPrint.h>


GameObject::GameObject(std::string _name, Vec2f _position, Vec2_ui32 _size)
{
    name = _name;
    position = _position;
    previousPosition = _position;
    size = _size;
    type = GameObjectType::GAME_OBJECT;

    graphicsComponent = std::make_shared<GraphicsComponent>();
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

const Vec2_ui32 &GameObject::getSize() const
{
    return size;
}

GameObjectType GameObject::getType()
{
    return type;
}

const Vec2f& GameObject::getPosition() const
{
    return position;
}

const Vec2f& GameObject::getPreviousPosition() const
{
    return previousPosition;
}

void GameObject::setPosition(const Vec2f &_position)
{
    previousPosition = position;
    position = _position;
}

void GameObject::setPositionX(float _x)
{
    previousPosition.x = position.x;
    position.x = _x;
}

void GameObject::setPositionY(float _y)
{
    previousPosition.y = position.y;
    position.y = _y;
}

bool GameObject::operator==(const GameObject &rhs) const
{
    return id == rhs.id;
}

bool GameObject::operator!=(const GameObject &rhs) const
{
    return id != rhs.id;
}