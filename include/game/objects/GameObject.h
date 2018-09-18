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
        std::string name;
        Vec2f position;
        Vec2f previousPosition;
        int width;
        int height;
        GameObjectType type;
        std::shared_ptr<Texture> texture;
        float renderTimeElapsed;
        float lastSpriteChangeTime;

    public:
        GameObject(std::string _name, Vec2f _position, int _width, int _height);
        virtual ~GameObject();

        virtual void draw(SDL_Renderer *renderer, float interp, float lastRenderTime);
        virtual void update(float deltaTime);

        uint32_t getId() const;
        void setId(uint32_t _id);
        std::string getName() const;
        const Vec2f &getPosition() const;
        const Vec2f &getPreviousPosition() const;
        void setPosition(const Vec2f &_position);
        void setPositionX(float _x);
        void setPositionY(float _y);

        int getWidth();
        int getHeight();
        GameObjectType getType();

        std::shared_ptr<Texture> getTexture();

        bool operator==(const GameObject &rhs) const;
        bool operator!=(const GameObject &rhs) const;
};

#endif