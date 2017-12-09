#ifndef ANRI_PLAYER_OBJECT_H
#define ANRI_PLAYER_OBJECT_H

#include <game/Color.h>
#include <game/objects/MovableGameObject.h>
#include <game/objects/IControllable.h>
#include <SDL_events.h>
#include <engine/input/Input.h>

class PlayerGameObject : public MovableGameObject
{
    public:
        PlayerGameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName, bool _collisionEnabled,
                         float _xVelocity, float _yVelocity, float _xAcceleration, float _yAcceleration, std::shared_ptr<Input> _input);
        void update(float deltaTime) override;

    private:
        std::shared_ptr<Input> input;

};

#endif