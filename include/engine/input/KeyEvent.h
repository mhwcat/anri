#ifndef ANRI_KEY_EVENT_H
#define ANRI_KEY_EVENT_H

#include "KeyEventType.h"
#include "KeyValue.h"

struct KeyEvent
{
	KeyEventType type;
	KeyValue value;
};

#endif