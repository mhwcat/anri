#include <game/Color.h>
#include <game/objects/GameObject.h>
#include <game/objects/MovableGameObject.h>


MovableGameObject::MovableGameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName,
                                     bool _collisionEnabled, float _xVelocity, float _yVelocity)
    : GameObject(_x, _y, _width, _height, _colorName, _collisionEnabled)
{
    xVelocity = _xVelocity;
    yVelocity = _yVelocity;

    type = GameObjectType::MOVABLE_GAME_OBJECT;
}

void MovableGameObject::move(float deltaTime)
{
    x += xVelocity * deltaTime;
    y += yVelocity * deltaTime;

    if(x < 0.f)
    {
        x -= xVelocity * deltaTime;
        xVelocity = 0.f;
    }

    if(y < 0.f)
    {
        y -= yVelocity * deltaTime;
        yVelocity = 0.f;
    }
}

float MovableGameObject::getXVelocity()
{
    return xVelocity;
}

float MovableGameObject::getYVelocity()
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