#include <engine/messaging/MessageSystem.h>
#include <engine/DebugPrint.h>

MessageSystem::MessageSystem()
{

}

MessageSystem::~MessageSystem()
{

}

Message* MessageSystem::getLastMessage(SystemType recipient)
{
    Message *msg = nullptr;
    if(!bus[recipient].empty())
    {
        msg = bus[recipient].front();
        bus[recipient].pop();
    }
    
    return msg;
}

bool MessageSystem::isQueueEmpty(SystemType recipient)
{
    return bus[recipient].empty();
}

void MessageSystem::postMessage(Message *message)
{
    bus[message->recipient].push(message);
}

