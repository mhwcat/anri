#include <memory>
#include <utility>
#include <vector>
#include <sstream>
#include <cmath>
#include <ctime>
#include <chrono>
#include <thread>
#include <engine/render/Renderer.h>
#include <engine/DebugPrint.h>
#include <engine/Config.h>


Renderer::Renderer()
{
    ANRI_DE debugPrint("Initializing Renderer subsystem.");

    frameTimeMs = 0.f;
    desiredFramesPerSecond = Config::getInstance().getIntValueByKey("renderer.fps");
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
                      std::string debugText)
{
    frameTimer.start();

    // Clear renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render objects
    for(auto const& go : objects)
    {
        go->draw(renderer);
    }

    // Render movables
    for(auto const& go : movables)
    {
        go->draw(renderer);
    }

    // Prepare debug text to render
    renderDebugText(std::move(debugText));

    // Main render
    SDL_RenderPresent(renderer);

    float frameTimeMicroseconds = (float) frameTimer.getMicrosecondsSinceStart();
    // If frame was rendered faster than desired, wait
    if((1000000.f / frameTimeMicroseconds) > desiredFramesPerSecond)
    {
        std::this_thread::sleep_for(std::chrono::microseconds((long) round(((1000000.f / desiredFramesPerSecond) - frameTimeMicroseconds))));
    }

    // Update frame time
    frameTimeMs = (frameTimeMicroseconds / 1000.f) + (round(((1000000.f / desiredFramesPerSecond) - frameTimeMicroseconds)) / 1000.f);
}

void Renderer::renderDebugText(std::string debugText)
{
    std::stringstream ss;
    ss.precision(4);
    ss << "Frame time: " << frameTimeMs << "ms" << std::endl;
    ss << debugText;

    SDL_Color color = {255, 255, 255};

    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(debugFont, ss.str().c_str(), color, 200);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect{};
    rect.x = windowWidth - 200;
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

    ANRI_DE debugPrint("Initializing renderer...");
    renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

    return true;
}

void Renderer::cleanup()
{
    ANRI_DE debugPrint("Shutting down SDL...");

    if(debugFont != nullptr)
        TTF_CloseFont(debugFont);
    if(renderer != nullptr)
        SDL_DestroyRenderer(renderer);
    if(window != nullptr)
        SDL_DestroyWindow(window);

    SDL_Quit();
}


