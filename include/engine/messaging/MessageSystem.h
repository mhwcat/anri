#ifndef ANRI_MESSAGE_SYSTEM_H
#define ANRI_MESSAGE_SYSTEM_H

#include <engine/messaging/Message.h>
#include <queue>
#include <map>

class MessageSystem 
{
    public:
        MessageSystem();
        ~MessageSystem();

        Message* getLastMessage(SystemType recipient);
        bool isQueueEmpty(SystemType recipient);
        void postMessage(Message* message);

    private:
        // Recipient -> queue of message pointers
        std::map<SystemType, std::queue<Message*> > bus = {
            { INPUT, std::queue<Message*>() },
            { GAME, std::queue<Message*>() },
            { EVENT_HANDLER, std::queue<Message*>() }
        };
};

#endif