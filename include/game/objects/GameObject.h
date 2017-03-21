#ifndef ANRI_GAME_OBJECT_H
#define ANRI_GAME_OBJECT_H

#include <memory>

#include <SDL_rect.h>
#include <game/objects/GameObjectType.h>
#include <game/Color.h>

class GameObject
{
	protected:
		uint32_t id;
		float x;
		float y;
		int width;
		int height;
		GameObjectType type;
		std::unique_ptr<Color> color;

	public:
		GameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName);
		virtual ~GameObject();

		uint32_t getId();
		void setId(uint32_t _id);
		float getX();
		float getY();
		int getWidth();
		int getHeight();
		std::unique_ptr<Color>& getColor();
		GameObjectType getType();
		SDL_Rect getSDLRect();
};

#endif