#ifndef ANRI_SDL_RENDERER_H
#define ANRI_SDL_RENDERER_H

#include <memory>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

#include <game/objects/GameObject.h>
#include <game/objects/MovableGameObject.h>
#include <engine/render/Renderer.h>
#include <engine/SimpleTimer.h>

class SDLRenderer : public Renderer 
{
	public:
		SDLRenderer();
		virtual ~SDLRenderer();
		bool init() override;
		void render(const std::vector<std::unique_ptr<GameObject> > &objects,
						const std::vector<std::shared_ptr<MovableGameObject> > &movables,
						std::string debugText) override;

	private:
		SDL_Renderer *renderer;
		SDL_Window *window;
		TTF_Font *debugFont;
		void renderDebugText(std::string debugText) override;
		void cleanup() override;
};

#endif