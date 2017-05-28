#include <engine/render/Renderer.h>
#include <engine/DebugPrint.h>
#include <engine/Config.h>

Renderer::Renderer()
{
    desiredFramesPerSecond = Config::getInstance().getIntValueByKey("renderer.fps");
    windowWidth = Config::getInstance().getIntValueByKey("window.width");
    windowHeight = Config::getInstance().getIntValueByKey("window.height");
}

Renderer::~Renderer()
{
    ANRI_DE debugPrint("Renderer destructor fired.");
}