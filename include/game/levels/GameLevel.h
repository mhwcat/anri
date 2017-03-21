#ifndef ANRI_GAME_LEVEL_H
#define ANRI_GAME_LEVEL_H

#include <vector>
#include <memory>
#include <cstdint>

#include <game/objects/GameObject.h>
#include <game/objects/PlayerGameObject.h>
#include <game/objects/MovableGameObject.h>

class GameLevel
{
	private:
		std::vector<std::unique_ptr<GameObject> > objects;
		std::vector<std::shared_ptr<MovableGameObject> > movables;
		std::shared_ptr<PlayerGameObject> player;
		uint32_t lastId;

	public:
		GameLevel();
		virtual ~GameLevel();

		const std::vector<std::unique_ptr<GameObject> >& getObjects() const;
		const std::vector<std::shared_ptr<MovableGameObject> >& getMovables() const;
		const std::shared_ptr<PlayerGameObject> &getPlayer() const;

		void setPlayer(std::shared_ptr<PlayerGameObject> playerGameObject);
		void addGameObject(std::unique_ptr<GameObject> gameObject);
		void addMovableGameObject(std::shared_ptr<MovableGameObject> movableGameObject);
		const std::unique_ptr<GameObject>& getGameObject(uint32_t id) const;
		void removeGameObject(uint32_t id);

};

#endif