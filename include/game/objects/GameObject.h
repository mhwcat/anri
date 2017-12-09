#ifndef ANRI_GAME_OBJECT_H
#define ANRI_GAME_OBJECT_H

#include <memory>

#include <SDL_rect.h>
#include <game/objects/GameObjectType.h>
#include <game/Color.h>
#include <SDL_render.h>

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
        bool collisionEnabled;
        bool colliding;

    public:
        GameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName, bool _collisionEnabled);
        virtual ~GameObject();

        virtual void draw(SDL_Renderer *renderer);
        virtual void update(float deltaTime);

        uint32_t getId();
        void setId(uint32_t _id);
        float getX();
        float getY();
        int getWidth();
        int getHeight();
        GameObjectType getType();
        std::unique_ptr<Color>& getColor();
        bool hasCollisionEnabled();
        void setCollisionEnabled(bool _collisionEnabled);
        bool isColliding();
        void setColliding(bool _colliding);

        bool operator==(const GameObject &rhs) const;
        bool operator!=(const GameObject &rhs) const;
};

#endif