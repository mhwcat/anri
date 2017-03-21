#ifndef ANRI_RENDERER_H
#define ANRI_RENDERER_H

#include <vector>
#include <memory>
#include <string>
#include "../../game/objects/GameObject.h"
#include "../../game/objects/MovableGameObject.h"
#include "../SimpleTimer.h"


class Renderer 
{
    public:
        virtual ~Renderer();
        virtual bool init() = 0;
        virtual void render(const std::vector<std::unique_ptr<GameObject> > &objects, 
                        const std::vector<std::shared_ptr<MovableGameObject> > &movables,
                        std::string debugText) = 0;
    private:
        std::unique_ptr<SimpleTimer> frameTimer;
        float frameTimeMs;
        void renderDebugText(std::string debugText);
        void cleanup();
};

#endif