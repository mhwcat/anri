#ifndef ANRI_GRAPHICS_COMPONENT_H
#define ANRI_GRAPHICS_COMPONENT_H

#include <engine/math/Vec2.h>
#include <engine/graphics/Texture.h>
#include <engine/Config.h>
#include <game/components/Component.h>
#include <memory>

class GraphicsComponent : public Component 
{
    private:
        const float TEXTURE_ANIM_FRAME_INTERVAL = 50.f;
        const bool DRAW_OUTLINES = Config::getInstance().getBoolValueByKey("renderer.drawOutlines");

        std::shared_ptr<Texture> texture;
        float renderTimeElapsed;
        float lastSpriteChangeTime;
    
    public:
        GraphicsComponent();
        void draw(SDL_Renderer *renderer, Vec2f previousPosition, Vec2f position, Vec2_ui32 size, float interp, float lastRenderTime);
        std::shared_ptr<Texture> getTexture();
        float getRenderTimeElapsed() const;
        float getLastSpriteChangeTime() const;        
        void setRenderTimeElapsed(float renderTimeElapsed);
        void setLastSpriteChangeTime(float lastSpriteChangeTime);
};

#endif