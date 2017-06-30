#include <engine/event/EventHandler.h>
#include <engine/DebugPrint.h>

EventHandler::EventHandler()
{
    ANRI_DE debugPrint("Initializing EventHandler subsystem.");
}

EventHandler::~EventHandler()
{
    ANRI_DE debugPrint("EventHandler destructor fired.");
}