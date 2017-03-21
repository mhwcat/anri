#include <game/Color.h>
#include <game/objects/GameObject.h>
#include <game/objects/MovableGameObject.h>


MovableGameObject::MovableGameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName, float _xVelocity, float _yVelocity) 
	: GameObject(_x, _y, _width, _height, _colorName)
{
	xVelocity = _xVelocity;
	yVelocity = _yVelocity;

	type = GameObjectType::MOVABLE_GAME_OBJECT;
}

void MovableGameObject::move(float deltaTime)
{
	x += xVelocity * deltaTime;
	y += yVelocity * deltaTime;
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