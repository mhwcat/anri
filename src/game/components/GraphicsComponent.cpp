#include <game/components/GraphicsComponent.h>
#include <game/objects/GameObjectType.h>
#include <engine/math/Vec2.h>
#include <engine/DebugPrint.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>

GraphicsComponent::GraphicsComponent(std::string _gameObjectName, std::shared_ptr<PhysicsComponent> _physicsComponent) 
{
    gameObjectName = _gameObjectName;
    physicsComponent = _physicsComponent;
    texture = std::make_shared<Texture>();
    renderTimeElapsed = 0.f;
    lastSpriteChangeTime = 0.f;
}

void GraphicsComponent::draw(SDL_Renderer *renderer, TTF_Font *debugFont, Vec2_ui32 size, float interp, float lastRenderTime)
{
    // Interpolation for rendering
    float drawX = physicsComponent->getPosition().x - (size.x / 2.f); //(previousPosition.x * interp) + (position.x * (1.f - interp));
    float drawY = physicsComponent->getPosition().y - (size.y / 2.f);//(previousPosition.y * interp) + (position.y * (1.f - interp));

    renderTimeElapsed += lastRenderTime;

    if(texture->isLoaded()) 
    {
        if((renderTimeElapsed - lastSpriteChangeTime) >= GraphicsComponent::TEXTURE_ANIM_FRAME_INTERVAL)
        {
            texture->nextSprite();
            lastSpriteChangeTime = renderTimeElapsed;
        }

        texture->draw((int) round(drawX), (int) round(drawY), (int) size.x, (int) size.y, physicsComponent->getRotationAngleDegrees(), renderer);
    }
    else 
    {
        // SDL_Rect rect { (int) round(drawX), (int) round(drawY), (int) size.x, (int) size.y };
        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // SDL_RenderFillRect(renderer, &rect);
    }

    if(DRAW_BODIES)
    {
        b2Vec2* vertices = physicsComponent->getBodyVertices();

        if(vertices != nullptr)
        {
            Sint16 vx[PhysicsComponent::POLYGON_VERTICES_COUNT];
            Sint16 vy[PhysicsComponent::POLYGON_VERTICES_COUNT];
            
            for(int i = 0; i < PhysicsComponent::POLYGON_VERTICES_COUNT; i++)
            {
                vx[i] = vertices[i].x;
                vy[i] = vertices[i].y;

                //debugPrint("vx[%d]=%d vy[%d]=%d", i, vx[i], i, vy[i]);
            }

            polygonColor(renderer, vx, vy, PhysicsComponent::POLYGON_VERTICES_COUNT, 0xFFA500FF);

            free(vertices);
        }
    }

    if(DRAW_DEBUG_PHYSICS_INFO) 
    {
        char textBuffer[64];

        uint32_t posX = physicsComponent->getPosition().x;
        uint32_t posY = physicsComponent->getPosition().y;

        snprintf(textBuffer, sizeof(textBuffer), "Pos: [%d, %d]\nVel: [%.2f, %.2f]\nRot: [%.2f]",
                posX,
                posY,
                physicsComponent->getVelocity().x,
                physicsComponent->getVelocity().y,
                physicsComponent->getRotationAngleDegrees()
        );

        SDL_Color color = {255, 255, 255};

        SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(debugFont, textBuffer, color, 200);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect rect{};
        rect.x = (int) round(posX + (size.x / 2.f) + 10);
        rect.y = (int) round(posY - (size.y / 2.f) - 20);

        SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
        SDL_RenderCopy(renderer, texture, nullptr, &rect);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
}

std::shared_ptr<Texture> GraphicsComponent::getTexture() 
{
    return texture;
}

float GraphicsComponent::getRenderTimeElapsed() const
{
    return renderTimeElapsed;
}

float GraphicsComponent::getLastSpriteChangeTime() const 
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