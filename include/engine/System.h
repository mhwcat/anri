#ifndef ANRI_SYSTEM_H
#define ANRI_SYSTEM_H

#include <engine/messaging/MessageSystem.h>
#include <memory>

class System 
{
    public:
        System();
        virtual ~System();
        virtual void handleEngineMessages() = 0;
        void setMessageSystem(std::shared_ptr<MessageSystem> _messageSystem);

    protected:
        std::shared_ptr<MessageSystem> messageSystem;
};

#endif