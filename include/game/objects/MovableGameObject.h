#ifndef ANRI_MOVABLE_GAME_OBJECT_H
#define ANRI_MOVABLE_GAME_OBJECT_H

#include <game/objects/GameObject.h>
#include <engine/Config.h>

class MovableGameObject : public GameObject
{
    protected:
        float xVelocity;
        float yVelocity;
        float xAcceleration;
        float yAcceleration;

        const float MAX_VELOCITY_X = 50.f;
        const float MAX_VELOCITY_Y = 50.f;

        const float Y_ACCELERATION_GRAVITY = (float) Config::getInstance().getIntValueByKey("physics.gravity");

    public:
        MovableGameObject(std::string _name, Vec2f _position, Vec2_ui32 _size,
                          float _xVelocity, float _yVelocity, float _xAcceleration, float _yAcceleration);

        void update(float deltaTime) override;
        void move(float directionDegrees, float acceleration);
        void stopMoving();

        float getXVelocity() const;
        void setXVelocity(float _xVelocity);
        float getYVelocity() const;
        void setYVelocity(float _yVelocity);
        float getXAcceleration() const;
        void setXAcceleration(float _xAcceleration);
        float getYAcceleration() const;
        void setYAcceleration(float _yAcceleration);
};

#endif