#ifndef ANRI_GAME_H
#define ANRI_GAME_H

#include <memory>
#include <engine/input/Input.h>
#include <engine/render/Renderer.h>
#include <engine/event/EventHandler.h>
#include <game/levels/GameLevel.h>


class Game 
{
	public:
		Game();
		virtual ~Game();

		void loadLevel(std::unique_ptr<GameLevel> level);
		bool init();
		void start();
		void stop();

	private:
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<EventHandler> eventHandler;
		std::unique_ptr<GameLevel> currentLevel;
		bool running;

		void mainLoop();
		void update(float deltaTime);
		void performEventHandling();
		std::string prepareDebugText();
};

#endif