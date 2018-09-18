#include <game/objects/ui/UiGameObject.h>
#include <game/objects/GameObject.h>
#include <engine/DebugPrint.h>

UiGameObject::UiGameObject(std::string _name, Vec2f _position, int _width, int _height) 
    : GameObject(_name, _position, _width, _height)
{
    texture->setAlpha(0);
    shown = false;
    fadeMode = UI_FADE_IN;
}

void UiGameObject::show() 
{
    shown = true;
}

void UiGameObject::draw(SDL_Renderer *renderer, float interp, float lastRenderTime)
{
    if(shown) 
    {
        if(texture->getAlpha() == 0)
        {
            if(fadeMode == UI_FADE_OUT)
            {
                shown = false;
                return;
            }
                
            fadeMode = UI_FADE_IN;
        }
        if(texture->getAlpha() == 255)
        {
            fadeMode = UI_FADE_OUT;
        }

        switch(fadeMode)
        {
            case UI_FADE_IN:
                fadeIn();
                break;
            case UI_FADE_OUT:
                fadeOut();
                break;
            
        }
    }

    GameObject::draw(renderer, interp, lastRenderTime);
}

void UiGameObject::fadeIn()
{
    if(texture->getAlpha() >= 0 && texture->getAlpha() < 255)
    {
        uint8_t val = 4;
        if((texture->getAlpha() + val) > 255)
        {
            texture->setAlpha(255);
        }
        else
        {
            texture->setAlpha(texture->getAlpha() + val);
        }
    }
}

void UiGameObject::fadeOut() 
{

    if(texture->getAlpha() > 0 && texture->getAlpha() <= 255)
    {
        uint8_t val = 1;
        if((texture->getAlpha() - val) < 0)
        {
            texture->setAlpha(0);
        }
        else 
        {
            texture->setAlpha(texture->getAlpha() - val);
        }
    }
}

