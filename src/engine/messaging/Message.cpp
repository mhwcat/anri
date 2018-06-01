#include <engine/messaging/Message.h>
#include <engine/Allocator.h>
#include <stdlib.h>

Message* createMessage(SystemType sender, SystemType recipient, MessageType type, void* data)
{
    Message *msg = (Message *) Allocator::getInstance().allocateMemory(sizeof(Message));
    msg->sender = sender;
    msg->recipient = recipient;
    msg->type = type;
    msg->data = data;

    return msg;
}

Message* createMessage(SystemType sender, SystemType recipient, MessageType type)
{
    return createMessage(sender, recipient, type, nullptr);
}