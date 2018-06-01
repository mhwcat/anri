#include <game/objects/GameObject.h>
#include <game/objects/MovableGameObject.h>
#include <engine/DebugPrint.h>
#include <math.h>


MovableGameObject::MovableGameObject(Vec2 _position, int _width, int _height, bool _collisionEnabled,
                                     float _xVelocity, float _yVelocity, float _xAcceleration,
                                     float _yAcceleration)
    : GameObject(_position, _width, _height, _collisionEnabled)
{
    xVelocity = _xVelocity;
    yVelocity = _yVelocity;
    xAcceleration = _xAcceleration;
    yAcceleration = _yAcceleration;

    type = GameObjectType::MOVABLE_GAME_OBJECT;
}

void MovableGameObject::update(float deltaTime) {
    if(xAcceleration == 0.f)
    {
        if(xVelocity > 0.f) {
            xVelocity -= 50.f * deltaTime;
            if(xVelocity < 0.f) xVelocity = 0.f;
        } else if(xVelocity < 0.f)
        {
            xVelocity += 50.f * deltaTime;
            if(xVelocity > 0.f) xVelocity = 0.f;
        }
    }

    xVelocity += xAcceleration * deltaTime;
    yVelocity += (yAcceleration + Y_ACCELERATION_GRAVITY) * deltaTime;

    if(xVelocity > MAX_VELOCITY_X)
    {
        xVelocity = MAX_VELOCITY_X;
    }
    if(xVelocity < -MAX_VELOCITY_X)
    {
        xVelocity = -MAX_VELOCITY_X;
    }

    if((position.y + height) > 658)
    {
        yAcceleration = 0.f;
        yVelocity = 0.f;
        setPositionY(658.f - height);
    }

    setPositionX(position.x + (xVelocity * deltaTime));
    setPositionY(position.y + (yVelocity * deltaTime));

    GameObject::update(deltaTime);
}

void MovableGameObject::move(float directionDegrees, float acceleration)
{
    float rad = 180.f / M_PI * directionDegrees;
    xAcceleration = acceleration * cos(rad);
    yAcceleration = acceleration * sin(rad);
}

void MovableGameObject::stopMoving()
{
    xAcceleration = 0.f;
    yAcceleration = 0.f;
}

float MovableGameObject::getXVelocity() const
{
    return xVelocity;
}

float MovableGameObject::getYVelocity() const
{
    return yVelocity;
}

void MovableGameObject::setXVelocity(float _xVelocity)
{
    xVelocity = _xVelocity;
}

void MovableGameObject::setYVelocity(float _yVelocity)
{
    yVelocity = _yVelocity;
}

float MovableGameObject::getXAcceleration() const {
    return xAcceleration;
}

void MovableGameObject::setXAcceleration(float _xAcceleration) {
    xAcceleration = _xAcceleration;
}

float MovableGameObject::getYAcceleration() const {
    return yAcceleration;
}

void MovableGameObject::setYAcceleration(float _yAcceleration) {
    yAcceleration = _yAcceleration;
}