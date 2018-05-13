#ifndef ANRI_MESSAGE_H
#define ANRI_MESSAGE_H

enum SystemType
{
    RENDER, INPUT, GAME, CAMERA,
};

enum MessageType 
{
    GAME_OBJECT_SET_POSITION,
    GAME_OBJECT_SET_ACCELERATION,
    
};

struct Message 
{
    SystemType sender;
    SystemType recipient;
    MessageType type;
    void* data;
};

#endif