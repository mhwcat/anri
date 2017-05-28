#ifndef ANRI_PLAYER_OBJECT_H
#define ANRI_PLAYER_OBJECT_H

#include <game/Color.h>
#include <game/objects/MovableGameObject.h>
#include <game/objects/IControllable.h>

class PlayerGameObject : public MovableGameObject, public IControllable
{
    public:
        PlayerGameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName, bool _collisionEnabled,
                         float _xVelocity, float _yVelocity);
        void handleInput(KeyEvent *keyEvent) override;
};

#endif