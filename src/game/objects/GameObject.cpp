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

void GameObject::update(float deltaTime)
{

}

void GameObject::draw(SDL_Renderer *renderer)
{
    SDL_Rect rect {
            (int) round(x),
            (int) round(y),
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
    return id != rhs.id;
}