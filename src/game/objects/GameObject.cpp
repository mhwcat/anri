#include <cmath>
#include <cstdint>
#include <memory>
#include <game/Color.h>
#include <game/objects/GameObject.h>
#include <engine/DebugPrint.h>


GameObject::GameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName, bool _collisionEnabled)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    color = std::make_unique<Color>(_colorName);
    collisionEnabled = _collisionEnabled;
    colliding = false;

    type = GameObjectType::GAME_OBJECT;
}

GameObject::~GameObject()
{
    ANRI_DE debugPrint("GameObject[%d] destructor fired.", id);
}

uint32_t GameObject::getId() 
{
    return id;
}

void GameObject::setId(uint32_t _id) 
{
    id = _id;
}

float GameObject::getX() 
{
    return x;
}

float GameObject::getY()
{
    return y;
}

int GameObject::getWidth()
{
    return width;
}

int GameObject::getHeight() 
{
    return height;
}

GameObjectType GameObject::getType()
{
    return type;
}

std::unique_ptr<Color>& GameObject::getColor() 
{
    return color;
}

bool GameObject::hasCollisionEnabled()
{
    return collisionEnabled;
}

void GameObject::setCollisionEnabled(bool _collisionEnabled)
{
    collisionEnabled = _collisionEnabled;
}

bool GameObject::isColliding()
{
    return colliding;
}

void GameObject::setColliding(bool _colliding)
{
    colliding = _colliding;
}

bool GameObject::operator==(const GameObject &rhs) const {
    return id == rhs.id;
}

bool GameObject::operator!=(const GameObject &rhs) const {
    return !(rhs == *this);
}

SDL_Rect GameObject::getSDLRect()
{
    SDL_Rect rect;
    rect.w = width;
    rect.h = height;
    rect.x = (int) round(x);
    rect.y = (int) round(y);

    return rect;
}