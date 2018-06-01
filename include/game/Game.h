#ifndef ANRI_GAME_H
#define ANRI_GAME_H

#include <memory>
#include <engine/input/Input.h>
#include <engine/render/Renderer.h>
#include <engine/event/EventHandler.h>
#include <game/levels/GameLevel.h>
#include <engine/sound/SoundSystem.h>


class Game : public System
{
    public:
        Game();
        virtual ~Game();

        void loadLevel(std::unique_ptr<GameLevel> level);
        bool init();
        void start();
        void stop();

        std::shared_ptr<Input> getInput();
        SDL_Renderer* getMainRenderer() const;

   private:
        std::unique_ptr<Renderer> renderer;
        std::shared_ptr<SoundSystem> soundSystem;
        std::shared_ptr<Input> input;
        std::unique_ptr<EventHandler> eventHandler;
        std::unique_ptr<GameLevel> currentLevel;
        bool running;
        uint64_t timeElapsed;
        float lastRenderTime;

        void mainLoop();
        void update(float deltaTime);
        void performEventHandling();
        std::string prepareDebugText();
        
        void handleEngineMessages() override;
};

#endif