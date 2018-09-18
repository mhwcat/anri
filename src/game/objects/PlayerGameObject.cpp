#include <game/objects/MovableGameObject.h>
#include <game/objects/PlayerGameObject.h>
#include <engine/DebugInfo.h>
#include <engine/DebugPrint.h>

PlayerGameObject::PlayerGameObject(std::string _name, Vec2f _position, int _width, int _height,
                                   float _xVelocity, float _yVelocity,
                                   float _xAcceleration, float _yAcceleration)
    : MovableGameObject(_name, _position, _width, _height, _xVelocity, _yVelocity, _xAcceleration, _yAcceleration)
{
    inAir = false;
    inAction = false;
    jumpTime = 0.f;

    type = GameObjectType::PLAYER_GAME_OBJECT;
}

void PlayerGameObject::update(float deltaTime)
{
    if(inAir) 
    {
        jumpTime += deltaTime;
        if(jumpTime > 0.15f)
        {
            yAcceleration = 0.f;
        }
    }

    if(inAction)
    {
        actionTime += deltaTime;
        if(actionTime > 1.5f)
        {
            inAction = false;
        }  
    }

    /*if(!input->isInputEventsQueueEmpty())
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
                if(input->wasKeyPressed(keycode) && !inAir)
                {
                    setPositionY(position.y - 1.f);
                    yAcceleration = -800.f;
                    inAir = true;
                    jumpTime = 0.f;
                } 
                break;
            case SDLK_ESCAPE:
                SDL_Event quitEvent{};
                quitEvent.type = SDL_QUIT;
                SDL_PushEvent(&quitEvent);
                break;
        }
    }*/

    DebugInfo::getInstance().playerPosition.x = position.x;
    DebugInfo::getInstance().playerPosition.y = position.y;
    DebugInfo::getInstance().playerVelocity.x = xVelocity;
    DebugInfo::getInstance().playerVelocity.y = yVelocity;

    if(inAir && (position.y + height) >= 510.0)
    {
        position.y = (510.f - height);
        yVelocity = 0.f;
        inAir = false;
        inAction = false;
    }

    MovableGameObject::update(deltaTime);
}

void PlayerGameObject::jump() 
{
    if(!inAir) 
    {
        setPositionY(position.y - 1.f);
        yAcceleration = -800.f;
        inAir = true;
        inAction = true;
        jumpTime = 0.f;
    }
}

void PlayerGameObject::executeAction()
{
    if(!inAction)
    {
        inAction = true;
        actionTime = 0.f;
        //texture->setTexture("player_action", texture->isFlippedHorizontal(), true);
    }
}

bool PlayerGameObject::isInAction()
{
    return inAction;
}