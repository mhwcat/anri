#ifndef ANRI_GAME_OBJECT_H
#define ANRI_GAME_OBJECT_H

#include <memory>
#include <map>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <game/objects/GameObjectType.h>
#include <engine/math/Vec2.h>
#include <engine/graphics/Texture.h>

class GameObject
{
    private:
        const float TEXTURE_ANIM_FRAME_INTERVAL = 50.f;
        
    protected:
        uint32_t id;
        Vec2 position;
        Vec2 previousPosition;
        int width;
        int height;
        GameObjectType type;
        bool collisionEnabled;
        bool colliding;
        std::shared_ptr<Texture> texture;
        float renderTimeElapsed;
        float lastSpriteChangeTime;

    public:
        GameObject(Vec2 _position, int _width, int _height, bool _collisionEnabled);
        virtual ~GameObject();

        virtual void draw(SDL_Renderer *renderer, float interp, float lastRenderTime);
        virtual void update(float deltaTime);

        uint32_t getId();
        void setId(uint32_t _id);
        const Vec2 &getPosition() const;
        const Vec2 &getPreviousPosition() const;
        void setPosition(const Vec2 &_position);
        void setPositionX(float _x);
        void setPositionY(float _y);

        int getWidth();
        int getHeight();
        GameObjectType getType();
        bool hasCollisionEnabled();
        void setCollisionEnabled(bool _collisionEnabled);
        bool isColliding();
        void setColliding(bool _colliding);

        std::shared_ptr<Texture> getTexture();

        bool operator==(const GameObject &rhs) const;
        bool operator!=(const GameObject &rhs) const;
};

#endif