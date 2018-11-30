#ifndef ANRI_PLAYER_OBJECT_H
#define ANRI_PLAYER_OBJECT_H

#include <game/objects/MovableGameObject.h>
#include <engine/input/Input.h>
#include <SDL_events.h>

class PlayerGameObject : public MovableGameObject
{
    public:
        PlayerGameObject(std::string _name, Vec2f _position, Vec2_ui32 _size, b2BodyType _bodyType, bool _fixedRotation,
                         float _xVelocity, float _yVelocity, float _xAcceleration, float _yAcceleration);
        void update(float deltaTime) override;
        // void move(float directionDegrees, float velocity);
        // void stopMoving();
        void jump();
        bool isInAction();
        void executeAction();

    private:
        bool inAir;
        bool inAction;
        float jumpTime;
        float actionTime;

};

#endif