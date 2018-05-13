#include <memory>
#include <vector>
#include <sstream>
#include <cmath>
#include <ctime>
#include <chrono>
#include <thread>
#include <engine/render/Renderer.h>
#include <engine/DebugPrint.h>
#include <engine/DebugInfo.h>
#include <SDL_image.h>

Renderer::Renderer()
{
    ANRI_DE debugPrint("Initializing Renderer subsystem.");

    windowWidth = Config::getInstance().getIntValueByKey("window.width");
    windowHeight = Config::getInstance().getIntValueByKey("window.height");
}

Renderer::~Renderer()
{
    ANRI_DE debugPrint("Renderer destructor fired.");
    cleanup();
}

void Renderer::render(const std::vector<std::unique_ptr<GameObject> > &objects,
                      const std::vector<std::shared_ptr<MovableGameObject> > &movables,
                      const std::vector<std::unique_ptr<ParticleSystem> > &particleSystems,
                      float interp,
                      float lastRenderTime)
{
    // Clear renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render objects
    for(auto const& go : objects)
    {
        go->draw(renderer, interp, lastRenderTime);
    }

    // Render movables
    for(auto const& go : movables)
    {
        go->draw(renderer, interp, lastRenderTime);
    }

    // Render particle systems
    for(auto const& ps : particleSystems)
    {
        ps->draw(renderer, interp);
    }

    // Render debug overlay
    ANRI_DE renderDebugText();

    // Main render
    SDL_RenderPresent(renderer);
}

void Renderer::renderDebugText()
{
    char textBuffer[256];

    snprintf(textBuffer, sizeof(textBuffer), "Render:     %.5fms\nUpdate:     %.5fms\nMem:        %.2fMB\nPlayer pos: [%.2f, %.2f]\nPlayer vel: [%.2f, %.2f]",
             DebugInfo::getInstance().renderTime,
             DebugInfo::getInstance().updateTime,
             DebugInfo::getInstance().memoryUsageBytes / 1024.f / 1024.f,
             DebugInfo::getInstance().playerPosition.x,
             DebugInfo::getInstance().playerPosition.y,
             DebugInfo::getInstance().playerVelocity.x,
             DebugInfo::getInstance().playerVelocity.y
    );

    SDL_Color color = {255, 255, 255};

    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(debugFont, textBuffer, color, 300);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect{};
    rect.x = windowWidth - 300;
    rect.y = 5;

    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

bool Renderer::init()
{
    ANRI_DE debugPrint("Initializing SDL and SDL Video subsystem...");
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

    debugFont = nullptr;
    debugFont = TTF_OpenFont(Config::getInstance().getStringValueByKey("debugOverlay.fontPath").c_str(),
                             Config::getInstance().getIntValueByKey("debugOverlay.fontSize"));
    if(debugFont == nullptr)
    {
        ANRI_DE debugPrint("Could not load debug font! TTF_Error: %s", TTF_GetError());
        return false;
    }

    ANRI_DE debugPrint("Initializing window...");
    window = nullptr;
    window = SDL_CreateWindow(Config::getInstance().getStringValueByKey("window.title").c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              windowWidth,
                              windowHeight,
                              SDL_WINDOW_SHOWN);
    if(window == nullptr)
    {
        ANRI_DE debugPrint("Window could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }
    else
    {
        ANRI_DE debugPrint("Initialized window with name \"%s\" and size %dx%d.",
                           Config::getInstance().getStringValueByKey("window.title").c_str(),
                           windowWidth,
                           windowHeight);
    }
    int windowMode = Config::getInstance().getIntValueByKey("window.mode");
    if(windowMode == 1)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    } else if(windowMode == 2)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }


    ANRI_DE debugPrint("Initializing renderer...");
    renderer = nullptr;
    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
    if(Config::getInstance().getIntValueByKey("renderer.vsyncEnabled") == 1)
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if(renderer == nullptr)
    {
        ANRI_DE debugPrint("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }
    else
    {
        SDL_RendererInfo info{};
        SDL_GetRendererInfo(renderer, &info);

        ANRI_DE debugPrint("Selected renderer: %s.", info.name);
    }

    // TODO: SDL_image initialization here, move it somewhere else later
    ANRI_DE debugPrint("Initializing SDL_image...");
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        ANRI_DE debugPrint( "SDL_image could not initialize! SDL_image Error: %s", IMG_GetError());
        return false;
    }

    return true;
}

void Renderer::cleanup()
{
    ANRI_DE debugPrint("Shutting down SDL...");

    if(debugFont != nullptr)
        TTF_CloseFont(debugFont);
    if(renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        //delete MAIN_RENDERER;
    }
    if(window != nullptr)
        SDL_DestroyWindow(window);

    IMG_Quit();

    TTF_Quit();

    SDL_Quit();
}

SDL_Renderer* Renderer::getRenderer() const 
{
    return renderer;
}


