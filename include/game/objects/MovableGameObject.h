#ifndef ANRI_MOVABLE_GAME_OBJECT_H
#define ANRI_MOVABLE_GAME_OBJECT_H

#include <game/objects/GameObject.h>
#include <game/objects/IMovable.h>

class MovableGameObject : public GameObject
{
    protected:
        float xVelocity;
        float yVelocity;
        float xAcceleration;
        float yAcceleration;

        const float MAX_VELOCITY_X = 50.f;
        const float MAX_VELOCITY_Y = 50.f;

    public:
        MovableGameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName, bool _collisionEnabled,
                          float _xVelocity, float _yVelocity, float _xAcceleration, float _yAcceleration);

        void update(float deltaTime) override;

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