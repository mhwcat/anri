#ifndef ANRI_GRAPHICS_COMPONENT_H
#define ANRI_GRAPHICS_COMPONENT_H

#include <SDL_ttf.h>
#include <engine/math/Vec2.h>
#include <engine/graphics/Texture.h>
#include <engine/Config.h>
#include <game/components/Component.h>
#include <game/components/PhysicsComponent.h>
#include <memory>

class GraphicsComponent : public Component 
{
    private:
        const float TEXTURE_ANIM_FRAME_INTERVAL = 50.f;
        const bool DRAW_BODIES = Config::getInstance().getBoolValueByKey("renderer.drawBodies");
        const bool DRAW_DEBUG_PHYSICS_INFO = Config::getInstance().getBoolValueByKey("renderer.drawDebugPhysicsInfo");

        std::string gameObjectName;
        std::shared_ptr<PhysicsComponent> physicsComponent;

        std::shared_ptr<Texture> texture;
        float renderTimeElapsed;
        float lastSpriteChangeTime;
    
    public:
        GraphicsComponent(std::string _gameObjectName, std::shared_ptr<PhysicsComponent> _physicsComponent);
        void draw(SDL_Renderer *renderer, TTF_Font *debugFont, Vec2_ui32 size, float interp, float lastRenderTime);
        std::shared_ptr<Texture> getTexture();
        float getRenderTimeElapsed() const;
        float getLastSpriteChangeTime() const;        
        void setRenderTimeElapsed(float renderTimeElapsed);
        void setLastSpriteChangeTime(float lastSpriteChangeTime);
};

#endif