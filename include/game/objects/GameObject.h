#ifndef ANRI_GAME_OBJECT_H
#define ANRI_GAME_OBJECT_H

#include <memory>
#include <map>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <game/objects/GameObjectType.h>
#include <engine/math/Vec2.h>
#include <game/components/GraphicsComponent.h>
#include <game/components/PhysicsComponent.h>

class GameObject
{       
    protected:
        uint32_t id;
        std::string name;
        Vec2_ui32 size;
        GameObjectType type;

        // Components
        std::shared_ptr<GraphicsComponent> graphicsComponent;
        std::shared_ptr<PhysicsComponent> physicsComponent;
        
    public:
        GameObject(std::string _name, Vec2f _position, Vec2_ui32 _size, b2BodyType _bodyType, bool _fixedRotation);
        virtual ~GameObject();

        virtual void update(float deltaTime);

        uint32_t getId() const;
        void setId(uint32_t _id);
        std::string getName() const;
        std::shared_ptr<GraphicsComponent> getGraphicsComponent();
        std::shared_ptr<PhysicsComponent> getPhysicsComponent();

        Vec2_ui32 getSize() const;
        GameObjectType getType() const;

        std::shared_ptr<Texture> getTexture();

        bool operator==(const GameObject &rhs) const;
        bool operator!=(const GameObject &rhs) const;
};

#endif