#ifndef ANRI_RENDERER_H
#define ANRI_RENDERER_H

#include <vector>
#include <memory>
#include <string>

#include <game/objects/GameObject.h>
#include <game/objects/MovableGameObject.h>
#include <engine/SimpleTimer.h>


class Renderer 
{
	public:
		Renderer();
		virtual ~Renderer();
		virtual bool init() = 0;
		virtual void render(const std::vector<std::unique_ptr<GameObject> > &objects,
						const std::vector<std::shared_ptr<MovableGameObject> > &movables,
						std::string debugText) = 0;
	protected:
		SimpleTimer frameTimer;
		float frameTimeMs;
		int desiredFramesPerSecond;
		int windowWidth;
		int windowHeight;
		virtual void renderDebugText(std::string debugText) = 0;
		virtual void cleanup() = 0;
};

#endif