#include <game/objects/MovableGameObject.h>
#include <game/objects/PlayerGameObject.h>

PlayerGameObject::PlayerGameObject(float _x, float _y, int _width, int _height, Color::ColorName _colorName,
                                   bool _collisionEnabled, float _xVelocity, float _yVelocity)
    : MovableGameObject(_x, _y, _width, _height, _colorName, _collisionEnabled, _xVelocity, _yVelocity)
{
    type = GameObjectType::PLAYER_GAME_OBJECT;
}

void PlayerGameObject::handleInput(InputEvent *keyEvent)
{
    if(keyEvent->type == InputEventType::KB_KEY_DOWN || keyEvent->type == InputEventType::PAD_BUTTON_DOWN)
    {
        switch(keyEvent->value)
        {
            case InputValue::KB_ARROW_UP:
            case InputValue::PAD_DPAD_UP:
                yVelocity = -50.f;
                break;
            case InputValue::KB_ARROW_DOWN:
            case InputValue::PAD_DPAD_DOWN:
                yVelocity = 50.f;
                break;
            case InputValue::KB_ARROW_LEFT:
            case InputValue::PAD_DPAD_LEFT:
                xVelocity = -50.f;
                break;
            case InputValue::KB_ARROW_RIGHT:
            case InputValue::PAD_DPAD_RIGHT:
                xVelocity = 50.f;
                break;
            default:
                break;
        }
    }
    else if(keyEvent->type == InputEventType::KB_KEY_UP || keyEvent->type == InputEventType::PAD_BUTTON_UP)
    {
        switch(keyEvent->value)
        {
            case InputValue::KB_ARROW_UP:
            case InputValue::KB_ARROW_DOWN:
            case InputValue::PAD_DPAD_UP:
            case InputValue::PAD_DPAD_DOWN:
                yVelocity = 0.f;
                break;
            case InputValue::KB_ARROW_LEFT:
            case InputValue::KB_ARROW_RIGHT:
            case InputValue::PAD_DPAD_LEFT:
            case InputValue::PAD_DPAD_RIGHT:
                xVelocity = 0.f;
                break;
            default:
                break;
        }
    }
}