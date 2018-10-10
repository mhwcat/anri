#include <game/components/GraphicsComponent.h>
#include <game/objects/GameObjectType.h>
#include <engine/math/Vec2.h>
#include <engine/DebugPrint.h>
#include <SDL_rect.h>
#include <SDL_render.h>

GraphicsComponent::GraphicsComponent() 
{
    texture = std::make_shared<Texture>();
    renderTimeElapsed = 0.f;
    lastSpriteChangeTime = 0.f;
}

void GraphicsComponent::draw(SDL_Renderer *renderer, Vec2f previousPosition, Vec2f position, Vec2_ui32 size, float interp, float lastRenderTime)
{
    // Interpolation for rendering
    float drawX = (previousPosition.x * interp) + (position.x * (1.f - interp));
    float drawY = (previousPosition.y * interp) + (position.y * (1.f - interp));

    renderTimeElapsed += lastRenderTime;

    if(texture->isLoaded()) 
    {
        if((renderTimeElapsed - lastSpriteChangeTime) >= GraphicsComponent::TEXTURE_ANIM_FRAME_INTERVAL)
        {
            texture->nextSprite();
            lastSpriteChangeTime = renderTimeElapsed;
        }

        texture->draw((int) round(drawX), (int) round(drawY), (int) size.x, (int) size.y, renderer);
    }
    else 
    {
        SDL_Rect rect { (int) round(drawX),(int) round(drawY), (int) size.x, (int) size.y };

        // if(type == PLAYER_GAME_OBJECT) 
        // {
        //     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        // }
        // else 
        // {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // }

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


std::shared_ptr<Texture> GraphicsComponent::getTexture() 
{
    return texture;
}

const float& GraphicsComponent::getRenderTimeElapsed() const
{
    return renderTimeElapsed;
}

const float& GraphicsComponent::getLastSpriteChangeTime() const 
{
    return lastSpriteChangeTime;
}

void GraphicsComponent::setRenderTimeElapsed(float _renderTimeElapsed) 
{
    renderTimeElapsed = _renderTimeElapsed;
}

void GraphicsComponent::setLastSpriteChangeTime(float _lastSpriteChangeTime)
{
    lastSpriteChangeTime = _lastSpriteChangeTime;
}


