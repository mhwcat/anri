#ifndef ANRI_RENDERER_H
#define ANRI_RENDERER_H

#include <memory>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

#include <game/objects/GameObject.h>
#include <game/objects/MovableGameObject.h>
#include <engine/graphics/ParticleSystem.h>
#include <engine/SimpleTimer.h>

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();
        bool init();
        void render(const std::vector<std::unique_ptr<GameObject> > &objects,
                    const std::vector<std::shared_ptr<MovableGameObject> > &movables,
                    const std::vector<std::unique_ptr<ParticleSystem> > &particleSystems,
                    float interp,
                    float lastRenderTime);
        void renderDebugText();
        void cleanup();
        SDL_Renderer* getRenderer() const;

    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        TTF_Font *debugFont;

        int windowWidth;
        int windowHeight;
};

#endif