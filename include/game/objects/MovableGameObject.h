#ifndef ANRI_MOVABLE_GAME_OBJECT_H
#define ANRI_MOVABLE_GAME_OBJECT_H

#include <game/objects/GameObject.h>
#include <game/objects/IMovable.h>

class MovableGameObject : public GameObject, public IMovable
{
    protected:
        float xVelocity;
        float yVelocity;
    
    public:
        MovableGameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName, float _xVelocity, float _yVelocity);

        void move(float deltaTime) override;

        float getXVelocity();
        float getYVelocity();
        void setXVelocity(float _xVelocity);
        void setYVelocity(float _yVelocity);
};

#endif