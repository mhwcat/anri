#ifndef ANRI_MESSAGE_SYSTEM_H
#define ANRI_MESSAGE_SYSTEM_H

class MessageSystem 
{
    public:
        MessageSystem();
        ~MessageSystem();

        std::unique_ptrgetMessage(Message.SystemType recipient);

    private:
        std::map<Message.SystemType, std::unique_ptr<Message> > bus;
}

#endif