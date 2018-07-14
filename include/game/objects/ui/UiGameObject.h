#ifndef ANRI_UI_GAME_OBJECT_H
#define ANRI_UI_GAME_OBJECT_H

#include <game/objects/GameObject.h>

enum UiFadeMode {
    UI_FADE_IN, UI_FADE_OUT
};

class UiGameObject : public GameObject
{
    private:
        float fadeInTime;
        float fadeOutTime;
        float displayTime;
        bool shown;
        UiFadeMode fadeMode;

        void fadeIn();
        void fadeOut();

    public:
        UiGameObject(std::string _name, Vec2 _position, int _width, int _height);
        void show();
        void draw(SDL_Renderer *renderer, float interp, float lastRenderTime) override;


};

#endif