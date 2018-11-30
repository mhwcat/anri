#include <game/objects/GameObject.h>
#include <game/objects/MovableGameObject.h>
#include <engine/DebugPrint.h>
#include <math.h>
#include <Box2D/Box2D.h>


MovableGameObject::MovableGameObject(std::string _name, Vec2f _position, Vec2_ui32 _size, b2BodyType _bodyType, bool _fixedRotation,
                                     float _xVelocity, float _yVelocity, float _xAcceleration,
                                     float _yAcceleration) 
    : GameObject(_name, _position, _size, _bodyType, _fixedRotation)
{
    xVelocity = _xVelocity;
    yVelocity = _yVelocity;
    xAcceleration = _xAcceleration;
    yAcceleration = _yAcceleration;

    type = GameObjectType::MOVABLE_GAME_OBJECT;
    physicsComponent->setBodyType(b2_dynamicBody);
}

void MovableGameObject::update(float deltaTime) 
{

    // if(type == PLAYER_GAME_OBJECT) 
    // {
    //     if(xAcceleration == 0.f)
    //     {
    //         if(xVelocity > 0.f) {
    //             xVelocity -= 50.f * deltaTime;
    //             if(xVelocity < 0.f) xVelocity = 0.f;
    //         } else if(xVelocity < 0.f)
    //         {
    //             xVelocity += 50.f * deltaTime;
    //             if(xVelocity > 0.f) xVelocity = 0.f;
    //         }
    //     }

    //     xVelocity += xAcceleration * deltaTime;
    //     yVelocity += (yAcceleration + 9.81f) * deltaTime;

    //     physicsComponent->setLinearVelocity(Vec2f{(xVelocity), (yVelocity)});

    // } else
    // {

    Vec2f vel{xAcceleration, yAcceleration};
    physicsComponent->applyForce(vel, deltaTime);

    GameObject::update(deltaTime);
}

void MovableGameObject::move(float directionDegrees, float acceleration)
{
    float rad = M_PI / 180.f * directionDegrees;

    xAcceleration = acceleration * cos(rad);
    yAcceleration = acceleration * sin(rad);

    //debugPrint("[%.5f, %.5f]", xAcceleration, yAcceleration);
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