#ifndef ANRI_INPUT_EVENT_H
#define ANRI_INPUT_EVENT_H

#include <engine/input/InputEventType.h>
#include <engine/input/InputValue.h>

struct InputEvent
{
    InputEventType type;
    InputValue value;
};

#endif