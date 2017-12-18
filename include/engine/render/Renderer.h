#ifndef ANRI_RENDERER_H
#define ANRI_RENDERER_H

#include <memory>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

#include <game/objects/GameObject.h>
#include <game/objects/MovableGameObject.h>
#include <engine/SimpleTimer.h>

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();
        bool init();
        void render(const std::vector<std::unique_ptr<GameObject> > &objects,
                    const std::vector<std::shared_ptr<MovableGameObject> > &movables,
                    std::string debugText, float alpha);
        void renderDebugText(std::string debugText);
        void cleanup();

    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        TTF_Font *debugFont;

        SimpleTimer frameTimer;
        float frameTimeMs;
        int desiredFramesPerSecond;
        int windowWidth;
        int windowHeight;
};

#endif