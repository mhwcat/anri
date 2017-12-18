#include <cmath>
#include <cstdint>
#include <memory>
#include <game/Color.h>
#include <game/objects/GameObject.h>
#include <engine/DebugPrint.h>


GameObject::GameObject(Vec2 _position, int _width, int _height, Color::ColorName _colorName, bool _collisionEnabled)
{
    position = _position;
    previousPosition = _position;
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

void GameObject::update(float deltaTime)
{

}

void GameObject::draw(SDL_Renderer *renderer, float alpha)
{
    // Interpolation for rendering
    float drawX = (previousPosition.x * alpha) + (position.x * (1.f - alpha));
    float drawY = (previousPosition.y * alpha) + (position.y * (1.f - alpha));

    SDL_Rect rect {
            (int) round(drawX),
            (int) round(drawY),
            width,
            height
    };

    SDL_SetRenderDrawColor(renderer, color->getR(), color->getG(), color->getB(), 255);
    SDL_RenderFillRect(renderer, &rect);
}

uint32_t GameObject::getId() 
{
    return id;
}

void GameObject::setId(uint32_t _id) 
{
    id = _id;
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

const Vec2 &GameObject::getPosition() const
{
    return position;
}

const Vec2 &GameObject::getPreviousPosition() const
{
    return previousPosition;
}

void GameObject::setPosition(const Vec2 &_position)
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