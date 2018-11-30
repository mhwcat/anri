#include <game/objects/MovableGameObject.h>
#include <game/objects/PlayerGameObject.h>
#include <engine/DebugInfo.h>
#include <engine/DebugPrint.h>

PlayerGameObject::PlayerGameObject(std::string _name, Vec2f _position, Vec2_ui32 _size, b2BodyType _bodyType, bool _fixedRotation,
                                   float _xVelocity, float _yVelocity,
                                   float _xAcceleration, float _yAcceleration)
    : MovableGameObject(_name, _position, _size, _bodyType, _fixedRotation, _xVelocity, _yVelocity, _xAcceleration, _yAcceleration)
{
    inAir = false;
    inAction = false;
    jumpTime = 0.f;

    type = GameObjectType::PLAYER_GAME_OBJECT;
}

void PlayerGameObject::update(float deltaTime)
{
    // if(inAction)
    // {
    //     actionTime += deltaTime;
    //     if(actionTime > 1.5f)
    //     {
    //         inAction = false;
    //     }  
    // }

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

                } 
                break;
            case SDLK_ESCAPE:
                SDL_Event quitEvent{};
                quitEvent.type = SDL_QUIT;
                SDL_PushEvent(&quitEvent);
                break;
        }
    }*/



    // if(xAcceleration == 0.f)
    // {
    //     if(xVelocity > 0.f) {
    //         xVelocity -= 100.f * deltaTime;
    //         if(xVelocity < 0.f) xVelocity = 0.f;
    //     } else if(xVelocity < 0.f)
    //     {
    //         xVelocity += 100.f * deltaTime;
    //         if(xVelocity > 0.f) xVelocity = 0.f;
    //     }
    // }

    // xVelocity += xAcceleration * deltaTime;
    // yVelocity += (yAcceleration) * deltaTime;

    // if(xVelocity > 100.f) {
    //     xVelocity = 100.f;
    // }
    // if(xVelocity < -100.f) {
    //     xVelocity = -100.f;
    // }

    // if(!inAir) {
    //     physicsComponent->setLinearVelocity(Vec2f{xVelocity, yVelocity});
    // }

    // if(inAir) {
    //     jumpTime += deltaTime;

    //     if(jumpTime > 0.5f) {
    //         inAir = false;
    //         physicsComponent->setLinearVelocity(Vec2f{physicsComponent->getVelocity().x, physicsComponent->getVelocity().y});
    //     }
    // }

    

    DebugInfo::getInstance().playerPosition.x = physicsComponent->getPosition().x;
    DebugInfo::getInstance().playerPosition.y = physicsComponent->getPosition().y;
    DebugInfo::getInstance().playerVelocity.x = physicsComponent->getVelocity().x;
    DebugInfo::getInstance().playerVelocity.y = physicsComponent->getVelocity().y;



    MovableGameObject::update(deltaTime);
}

// void PlayerGameObject::move(float directionDegrees, float velocity)
// {
//     float rad = M_PI / 180.f * directionDegrees;

//     xVelocity = velocity * cos(rad);
//     yVelocity = velocity * sin(rad);

//     debugPrint("[%.5f, %.5f]", xVelocity, yVelocity);
// }

// void PlayerGameObject::stopMoving()
// {
//     xVelocity = 0.f;
//     yVelocity = 0.f;
// }

void PlayerGameObject::jump() 
{
    physicsComponent->applyLinearImpulse(Vec2f{0.f, -80.f});
    // if(!inAir) 
    // {
    //     inAir = true;
    //     jumpTime = 0.f;
    // }
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