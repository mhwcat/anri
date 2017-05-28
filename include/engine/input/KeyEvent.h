#ifndef ANRI_KEY_EVENT_H
#define ANRI_KEY_EVENT_H

#include <engine/input/KeyEventType.h>
#include <engine/input/KeyValue.h>

struct KeyEvent
{
    KeyEventType type;
    KeyValue value;
};

#endif