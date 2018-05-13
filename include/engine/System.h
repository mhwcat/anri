#ifndef ANRI_SYSTEM_H
#define ANRI_SYSTEM_H

class System 
{
    public:
        virtual ~System();
        virtual void handleMessage(std::unique_ptr<Message> message);

    protected:
        std::shared_ptr<MessageSystem> messageSystem;
}

#endif