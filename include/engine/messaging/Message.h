#ifndef ANRI_MESSAGE_H
#define ANRI_MESSAGE_H

enum SystemType
{
    RENDER, AINPUT, GAME, CAMERA, EVENT_HANDLER
};

enum MessageType 
{
    GAME_SHUTDOWN,

    PLAYER_MOVE,                // generic move, angle must be specified
    PLAYER_STOP_MOVING,         // set acceleration to 0
    PLAYER_WALK_LEFT,           // move left with texture switch
    PLAYER_WALK_RIGHT,          // move right with texture switch
    PLAYER_STOP_WALKING,        // stop moving with texture switch
    PLAYER_JUMP,
    PLAYER_ATTACK,
    PLAYER_ACTION,
    PLAYER_SWITCH_TEXTURE,      // switch texture

    PARTICLE_SYSTEM_ADD,
    
};

struct Message 
{
    SystemType sender;
    SystemType recipient;
    MessageType type;
    void* data;
};

Message* createMessage(SystemType sender, SystemType recipient, MessageType type, void* data);
Message* createMessage(SystemType sender, SystemType recipient, MessageType type);

#endif