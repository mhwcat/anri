#include <engine/System.h>
#include <engine/DebugPrint.h>

System::System() 
{

}

System::~System() 
{

}

void System::setMessageSystem(std::shared_ptr<MessageSystem> _messageSystem)
{
    messageSystem = _messageSystem;
}