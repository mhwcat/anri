#ifndef ANRI_PLAYER_OBJECT_H
#define ANRI_PLAYER_OBJECT_H

#include <game/objects/MovableGameObject.h>
#include <game/objects/IControllable.h>
#include <engine/input/Input.h>
#include <SDL_events.h>

class PlayerGameObject : public MovableGameObject
{
    public:
        PlayerGameObject(Vec2 _position, int _width, int _height, bool _collisionEnabled,
                         float _xVelocity, float _yVelocity, float _xAcceleration, float _yAcceleration, std::shared_ptr<Input> _input);
        void update(float deltaTime) override;

        void jump();

    private:
        std::shared_ptr<Input> input;
        bool inAir;
        float jumpTime;

};

#endif