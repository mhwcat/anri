#ifndef ANRI_GAME_OBJECT_H
#define ANRI_GAME_OBJECT_H

#include <memory>
#include <map>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <game/objects/GameObjectType.h>
#include <engine/math/Vec2.h>
#include <game/components/GraphicsComponent.h>

class GameObject
{       
    protected:
        uint32_t id;
        std::string name;
        Vec2f position;
        Vec2f previousPosition;
        Vec2_ui32 size;
        GameObjectType type;

        // Components
        std::shared_ptr<GraphicsComponent> graphicsComponent;


    public:
        GameObject(std::string _name, Vec2f _position, Vec2_ui32 _size);
        virtual ~GameObject();

        virtual void update(float deltaTime);

        uint32_t getId() const;
        void setId(uint32_t _id);
        std::string getName() const;
        std::shared_ptr<GraphicsComponent> getGraphicsComponent();

        Vec2f getPosition() const;
        Vec2f getPreviousPosition() const;
        void setPosition(Vec2f _position);
        void setPositionX(float _x);
        void setPositionY(float _y);

        Vec2_ui32 getSize() const;
        GameObjectType getType() const;

        std::shared_ptr<Texture> getTexture();

        bool operator==(const GameObject &rhs) const;
        bool operator!=(const GameObject &rhs) const;
};

#endif