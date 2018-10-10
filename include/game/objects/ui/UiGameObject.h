#ifndef ANRI_UI_GAME_OBJECT_H
#define ANRI_UI_GAME_OBJECT_H

#include <game/objects/GameObject.h>

class UiGameObject : public GameObject
{
    private:
        float fadeInTime;
        float fadeOutTime;
        float displayTime;
        bool shown;
};

#endif