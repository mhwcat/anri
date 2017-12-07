#include <engine/input/Input.h>
#include <engine/DebugPrint.h>

Input::Input()
{
    ANRI_DE debugPrint("Initializing Input subsystem.");
}

Input::~Input()
{
    ANRI_DE debugPrint("Input destructor fired.");
}

Input::AnalogStickAxisValues Input::getAnalogStickAxisValues()
{
    return analogStickAxisValues;
}