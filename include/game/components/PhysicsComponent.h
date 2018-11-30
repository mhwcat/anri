#ifndef ANRI_PHYSICS_COMPONENT_H
#define ANRI_PHYSICS_COMPONENT_H

#include <engine/math/Vec2.h>
#include <engine/physics/World.h>
#include <game/components/Component.h>
#include <Box2D/Box2D.h>
#include <memory>

class PhysicsComponent : public Component 
{
    private:
        std::string gameObjectName;
        Vec2f originPosition;
        Vec2_ui32 originSize;
        bool fixedRotation;

        // Box2D
        b2BodyType bodyType;
        bool hasBodyType = false;
        std::shared_ptr<b2World> world = World::getInstance().getWorld();
        b2Body* body = nullptr;
    
    public:
        static const int POLYGON_VERTICES_COUNT = 4;

        PhysicsComponent(std::string _gameObjectName, Vec2f _originPosition, Vec2_ui32 _originSize, b2BodyType _bodyType, bool _fixedRotation);
        virtual ~PhysicsComponent();

        void initBody();
        void update();

        void applyForce(Vec2f& force, float deltaTime);
        void setVelocity(Vec2f& velocity);
        void setLinearVelocity(Vec2f velocity);
        void applyLinearImpulse(Vec2f impulse);
        b2Vec2* getBodyVertices();
        float getRotationAngleDegrees();
        Vec2_ui32 getPosition();
        Vec2f getVelocity();
        void setBodyType(b2BodyType _bodyType);
        bool isBodyTypeSet();
        void setTransform(Vec2f _transform, float _angle);
};

#endif