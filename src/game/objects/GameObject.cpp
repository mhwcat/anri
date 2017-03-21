#include <cmath>
#include <cstdint>
#include <memory>
#include <game/Color.h>
#include <game/objects/GameObject.h>
#include <engine/DebugPrint.h>
#include "SDL.h"


GameObject::GameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName) 
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	color = std::make_unique<Color>(_colorName);

	type = GameObjectType::GAME_OBJECT;
}

GameObject::~GameObject()
{
	ANRI_DE debugPrint("GameObject[%d] destructor fired.", id);
}

uint32_t GameObject::getId() 
{
	return id;
}

void GameObject::setId(uint32_t _id) 
{
	id = _id;
}

float GameObject::getX() 
{
	return x;
}

float GameObject::getY()
{
	return y;
}

int GameObject::getWidth()
{
	return width;
}

int GameObject::getHeight() 
{
	return height;
}

std::unique_ptr<Color>& GameObject::getColor() 
{
	return color;
}

GameObjectType GameObject::getType() 
{
	return type;
}

SDL_Rect GameObject::getSDLRect()
{
	SDL_Rect rect;
	rect.w = width;
	rect.h = height;
	rect.x = (int) round(x);
	rect.y = (int) round(y);

	return rect;
}