#include <game/objects/MovableGameObject.h>
#include <game/objects/PlayerGameObject.h>
#include <engine/DebugPrint.h>

PlayerGameObject::PlayerGameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName,
                                   bool _collisionEnabled, float _xVelocity, float _yVelocity,
                                   float _xAcceleration, float _yAcceleration, std::shared_ptr<Input> _input)
    : MovableGameObject(_x, _y, _width, _height, _colorName, _collisionEnabled, _xVelocity, _yVelocity, _xAcceleration, _yAcceleration)
{
    input = _input;

    type = GameObjectType::PLAYER_GAME_OBJECT;
}

void PlayerGameObject::update(float deltaTime)
{
    if(!input.get()->isInputEventsQueueEmpty())
    {
        SDL_Keycode keycode = input.get()->getLastInputEventAndPop().key.keysym.sym;

        if(keycode == SDLK_RIGHT)
        {
            if(input.get()->isKeyHeld(keycode))
            {
                xAcceleration = 10.f;
            } else if(input.get()->wasKeyReleased(keycode))
            {
                xAcceleration = 0.f;
            }
        }

        if(keycode == SDLK_LEFT)
        {
            if(input.get()->isKeyHeld(keycode))
            {
                xAcceleration = -10.f;
            } else if(input.get()->wasKeyReleased(keycode))
            {
                xAcceleration = 0.f;
            }
        }
    }

    MovableGameObject::update(deltaTime);
}