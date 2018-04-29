#include <cmath>
#include <cstdint>
#include <memory>
#include <game/objects/GameObject.h>
#include <engine/DebugPrint.h>


GameObject::GameObject(Vec2 _position, int _width, int _height, bool _collisionEnabled)
{
    position = _position;
    previousPosition = _position;
    width = _width;
    height = _height;
    collisionEnabled = _collisionEnabled;
    colliding = false;
    texture = std::make_shared<Texture>();
    frameCounter = 0;

    type = GameObjectType::GAME_OBJECT;
}

GameObject::~GameObject()
{
    ANRI_DE debugPrint("GameObject[%d] destructor fired.", id);
}

void GameObject::update(float deltaTime)
{

}

void GameObject::draw(SDL_Renderer *renderer, float interp)
{
    // Interpolation for rendering
    float drawX = (previousPosition.x * interp) + (position.x * (1.f - interp));
    float drawY = (previousPosition.y * interp) + (position.y * (1.f - interp));

    if(texture->isLoaded()) 
    {
        if(frameCounter % 4 == 0)
        {
            texture->nextSprite();
        }
        texture->draw((int) round(drawX), (int) round(drawY), width, height, renderer);
    }
    else 
    {
        SDL_Rect rect { (int) round(drawX),(int) round(drawY), width, height };

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    frameCounter++;
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

std::shared_ptr<Texture> GameObject::getTexture() 
{
    return texture;
}

bool GameObject::operator==(const GameObject &rhs) const
{
    return id == rhs.id;
}

bool GameObject::operator!=(const GameObject &rhs) const
{
    return id != rhs.id;
}