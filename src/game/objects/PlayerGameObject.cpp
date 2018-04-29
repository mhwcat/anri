#include <game/objects/MovableGameObject.h>
#include <game/objects/PlayerGameObject.h>
#include <engine/DebugInfo.h>

PlayerGameObject::PlayerGameObject(Vec2 _position, int _width, int _height,
                                   bool _collisionEnabled, float _xVelocity, float _yVelocity,
                                   float _xAcceleration, float _yAcceleration, std::shared_ptr<Input> _input)
    : MovableGameObject(_position, _width, _height, _collisionEnabled, _xVelocity, _yVelocity, _xAcceleration, _yAcceleration)
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
                    texture->setTexture("player_walk", true);

                } else if(input->wasKeyReleased(keycode))
                {
                    xAcceleration = 0.f;
                    texture->setTexture("player_idle", true);

                }
                break;
            case SDLK_RIGHT:
                if(input->isKeyHeld(keycode))
                {
                    texture->setTexture("player_walk", false);
                    xAcceleration = 30.f;
                } else if(input->wasKeyReleased(keycode))
                {
                    texture->setTexture("player_idle", false);
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
            case SDLK_ESCAPE:
                SDL_Event quitEvent{};
                quitEvent.type = SDL_QUIT;
                SDL_PushEvent(&quitEvent);
                break;
        }
    }

    DebugInfo::getInstance().playerPosition.x = position.x;
    DebugInfo::getInstance().playerPosition.y = position.y;
    DebugInfo::getInstance().playerVelocity.x = xVelocity;
    DebugInfo::getInstance().playerVelocity.y = yVelocity;

    MovableGameObject::update(deltaTime);
}