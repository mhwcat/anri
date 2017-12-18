#include <game/objects/MovableGameObject.h>
#include <game/objects/PlayerGameObject.h>
#include <engine/DebugPrint.h>

PlayerGameObject::PlayerGameObject(Vec2 _position, int _width, int _height, Color::ColorName _colorName,
                                   bool _collisionEnabled, float _xVelocity, float _yVelocity,
                                   float _xAcceleration, float _yAcceleration, std::shared_ptr<Input> _input)
    : MovableGameObject(_position, _width, _height, _colorName, _collisionEnabled, _xVelocity, _yVelocity, _xAcceleration, _yAcceleration)
{
    input = _input;

    type = GameObjectType::PLAYER_GAME_OBJECT;
}

void PlayerGameObject::update(float deltaTime)
{
    if(!input->isInputEventsQueueEmpty())
    {
        SDL_Keycode keycode = input->getLastInputEventAndPop().key.keysym.sym;

        switch(keycode)
        {
            case SDLK_LEFT:
                if(input->isKeyHeld(keycode))
                {
                    xAcceleration = -30.f;
                } else if(input->wasKeyReleased(keycode))
                {
                    xAcceleration = 0.f;
                }
                break;
            case SDLK_RIGHT:
                if(input->isKeyHeld(keycode))
                {
                    xAcceleration = 30.f;
                } else if(input->wasKeyReleased(keycode))
                {
                    xAcceleration = 0.f;
                }
                break;
            case SDLK_SPACE:
                if(input->wasKeyPressed(keycode))
                {
                    setPositionY(position.y - 1.f);
                    yAcceleration = -50.f;
                } else if(input->wasKeyReleased(keycode)) {
                    yAcceleration = 0.f;
                }
                break;
        }
    }

    MovableGameObject::update(deltaTime);
}