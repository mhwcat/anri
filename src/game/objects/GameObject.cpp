#include <cmath>
#include <cstdint>
#include <memory>
#include <game/objects/GameObject.h>
#include <engine/DebugPrint.h>


GameObject::GameObject(std::string _name, Vec2f _position, int _width, int _height)
{
    name = _name;
    position = _position;
    previousPosition = _position;
    width = _width;
    height = _height;
    texture = std::make_shared<Texture>();
    renderTimeElapsed = 0.f;
    lastSpriteChangeTime = 0.f;

    type = GameObjectType::GAME_OBJECT;
}

GameObject::~GameObject()
{
    ANRI_DE debugPrint("GameObject[%d] destructor fired.", id);
}

void GameObject::update(float deltaTime)
{

}

void GameObject::draw(SDL_Renderer *renderer, float interp, float lastRenderTime)
{
    // Interpolation for rendering
    float drawX = (previousPosition.x * interp) + (position.x * (1.f - interp));
    float drawY = (previousPosition.y * interp) + (position.y * (1.f - interp));

    renderTimeElapsed += lastRenderTime;

    if(texture->isLoaded()) 
    {
        if((renderTimeElapsed - lastSpriteChangeTime) >= TEXTURE_ANIM_FRAME_INTERVAL)
        {
            texture->nextSprite();
            lastSpriteChangeTime = renderTimeElapsed;
        }

        texture->draw((int) round(drawX), (int) round(drawY), width, height, renderer);
    }
    else 
    {
        SDL_Rect rect { (int) round(drawX),(int) round(drawY), width, height };

        if(type == PLAYER_GAME_OBJECT) 
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        else 
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }

        SDL_RenderFillRect(renderer, &rect);
    }

    // Outline movables
    // if(type == MOVABLE_GAME_OBJECT || type == PLAYER_GAME_OBJECT) 
    // {
    //     SDL_Rect outline { (int) round(drawX),(int) round(drawY), width, height };
    //     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //     SDL_RenderDrawRect(renderer, &outline);
    // }
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

const Vec2f &GameObject::getPosition() const
{
    return position;
}

const Vec2f &GameObject::getPreviousPosition() const
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