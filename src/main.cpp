#include <cstdio>
#include <cstdlib>
#include <memory>

#include <game/Color.h>
#include <game/levels/GameLevel.h>
#include <game/Game.h>
#include <engine/DebugPrint.h>
#include <engine/Config.h>

int main(int argc, char* args[])
{
	std::unique_ptr<Game> g = std::make_unique<Game>();
	if(!g->init())
	{
		ANRI_DE debugPrint("Game init failed!");

		return EXIT_FAILURE;
	}

	std::unique_ptr<GameLevel> gl = std::make_unique<GameLevel>();
	gl->addGameObject(std::make_unique<GameObject>(10, 10, 10, 10, Color::ColorName::RED));
	gl->addMovableGameObject(std::make_shared<MovableGameObject>(10, 10, 15, 15, Color::ColorName::GREEN, 10.f, 10.f));
	gl->setPlayer(std::make_shared<PlayerGameObject>(10, 10, 10, 10, Color::ColorName::BLUE, 0.f, 0.f));
	g->loadLevel(std::move(gl));

	g->start();

	ANRI_DE debugPrint("Exitting gracefully...");

	return EXIT_SUCCESS;
}


