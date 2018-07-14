#ifndef ANRI_PLAYER_OBJECT_H
#define ANRI_PLAYER_OBJECT_H

#include <game/objects/MovableGameObject.h>
#include <game/objects/IControllable.h>
#include <engine/input/Input.h>
#include <SDL_events.h>

class PlayerGameObject : public MovableGameObject
{
    public:
        PlayerGameObject(std::string _name, Vec2 _position, int _width, int _height, bool _collisionEnabled,
                         float _xVelocity, float _yVelocity, float _xAcceleration, float _yAcceleration, std::shared_ptr<Input> _input);
        void update(float deltaTime) override;

        void jump();
        bool isInAction();
        void executeAction();

    private:
        std::shared_ptr<Input> input;
        bool inAir;
        bool inAction;
        float jumpTime;
        float actionTime;

};

#endif