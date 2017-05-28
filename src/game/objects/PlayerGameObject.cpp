#include <game/objects/MovableGameObject.h>
#include <game/objects/PlayerGameObject.h>

PlayerGameObject::PlayerGameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName,
                                   bool _collisionEnabled, float _xVelocity, float _yVelocity)
    : MovableGameObject(_x, _y, _width, _height, _colorName, _collisionEnabled, _xVelocity, _yVelocity)
{
    type = GameObjectType::PLAYER_GAME_OBJECT;
}

void PlayerGameObject::handleInput(KeyEvent *keyEvent)
{
    if(keyEvent->type == KeyEventType::KEY_DOWN)
    {
        switch(keyEvent->value)
        {
            case KeyValue::ARROW_UP:
                yVelocity = -50.f;
                break;
            case KeyValue::ARROW_DOWN:
                yVelocity = 50.f;
                break;
            case KeyValue::ARROW_LEFT:
                xVelocity = -50.f;
                break;
            case KeyValue::ARROW_RIGHT:
                xVelocity = 50.f;
                break;
            default:
                break;
        }
    }
    else if(keyEvent->type == KeyEventType::KEY_UP)
    {
        switch(keyEvent->value)
        {
            case KeyValue::ARROW_UP:
            case KeyValue::ARROW_DOWN:
                yVelocity = 0.f;
                break;
            case KeyValue::ARROW_LEFT:
            case KeyValue::ARROW_RIGHT:
                xVelocity = 0.f;
                break;
            default:
                break;
        }
    }
}