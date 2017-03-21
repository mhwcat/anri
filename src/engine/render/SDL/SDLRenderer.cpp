#include <memory>
#include <vector>
#include <sstream>
#include <cmath>
#include <ctime>
#include <chrono>
#include <thread>
#include <engine/render/Renderer.h>
#include <engine/render/SDL/SDLRenderer.h>
#include <engine/DebugPrint.h>
#include <game/Globals.h>


SDLRenderer::SDLRenderer() : Renderer()
{
    frameTimeMs = 0.f;
}

SDLRenderer::~SDLRenderer()
{
    cleanup();
}

void SDLRenderer::render(const std::vector<std::unique_ptr<GameObject> > &objects, 
                            const std::vector<std::shared_ptr<MovableGameObject> > &movables,
                            std::string debugText)
{
    frameTimer.start();

    // Render background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render objects
    for(auto const& go : objects)
    {
        SDL_Rect rect = go->getSDLRect();

        SDL_SetRenderDrawColor(renderer, go->getColor()->getR(), go->getColor()->getG(), go->getColor()->getB(), 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    // Render movables
    for(auto const& go : movables)
    {
        SDL_Rect rect = go->getSDLRect();

        SDL_SetRenderDrawColor(renderer, go->getColor()->getR(), go->getColor()->getG(), go->getColor()->getB(), 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    // Prepare debug text to render
    renderDebugText(debugText);

    // Main render
    SDL_RenderPresent(renderer);

    float frameTimeMicroseconds = (float) frameTimer.getMicrosecondsSinceStart();
    // If frame was rendered faster than desired, wait
    if((1000000.f / frameTimeMicroseconds) > ANRI_FRAMES_PER_SECOND)
    {
        std::this_thread::sleep_for(std::chrono::microseconds((long) round(((1000000.f / ANRI_FRAMES_PER_SECOND) - frameTimeMicroseconds))));
    }

    // Update frame time
    frameTimeMs = (frameTimeMicroseconds / 1000.f) + (round(((1000000.f / ANRI_FRAMES_PER_SECOND) - frameTimeMicroseconds)) / 1000.f);
}

void SDLRenderer::renderDebugText(std::string debugText)
{
    std::stringstream ss;
    ss.precision(4);
    ss << "Frame time: " << frameTimeMs << "ms" << std::endl;
    ss << debugText;

    SDL_Color color = {255, 255, 255};

    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(debugFont, ss.str().c_str(), color, 200);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.x = ANRI_WINDOW_WIDTH - 200;
    rect.y = 5;

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

bool SDLRenderer::init()
{
    ANRI_DE debugPrint("Initializing SDL...");
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        ANRI_DE debugPrint("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }

    ANRI_DE debugPrint("Initializing SDL_TTF...");
    if(TTF_Init() < 0)
    {
        ANRI_DE debugPrint("SDL_TTF could not initialize! TTF_Error: %s", TTF_GetError());
        return false;    
    }

    debugFont = NULL;
    debugFont = TTF_OpenFont(ANRI_DEBUG_FONT_PATH, ANRI_DEBUG_FONT_SIZE);
    if(debugFont == NULL)
    {
        ANRI_DE debugPrint("Could not load debug font! TTF_Error: %s", TTF_GetError());
        return false;    
    }

    ANRI_DE debugPrint("Initializing window...");
    window = NULL;
    window = SDL_CreateWindow(ANRI_WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANRI_WINDOW_WIDTH, ANRI_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        ANRI_DE debugPrint("Window could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }
    else
    {
        ANRI_DE debugPrint("Initialized window with name \"%s\" and size %dx%d.", ANRI_WINDOW_NAME, ANRI_WINDOW_WIDTH, ANRI_WINDOW_HEIGHT);
    }

    ANRI_DE debugPrint("Initializing renderer...");
    renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        ANRI_DE debugPrint("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }
    else
    {
        SDL_RendererInfo info;
        SDL_GetRendererInfo(renderer, &info);

        ANRI_DE debugPrint("Selected renderer: %s.", info.name);
    }

    return true;
}

void SDLRenderer::cleanup()
{
    ANRI_DE debugPrint("Shutting down SDL...");

    if(debugFont != NULL)
        TTF_CloseFont(debugFont);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);

    SDL_Quit();
}


