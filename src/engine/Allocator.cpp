#include <engine/Allocator.h>
#include <engine/DebugPrint.h>
#include <stdlib.h>
#include <string.h>


Allocator::Allocator() 
{
    ANRI_DE debugPrint("Initializing Allocator with %d bytes memory pool size.", ALLOC_MEM_SIZE);

    startPointer = (void *) malloc(ALLOC_MEM_SIZE);
    offset = 0;
}

Allocator::~Allocator()
{
    ANRI_DE debugPrint("Allocator destructor fired.");

    free(startPointer);
    startPointer = nullptr;
}

Allocator& Allocator::getInstance()
{
    static Allocator instance;
    return instance;
}

void* Allocator::allocateMemory(std::size_t size) 
{
    const std::size_t currentMemoryAddress = (std::size_t) startPointer + offset;

    if(currentMemoryAddress > (std::size_t) startPointer + ALLOC_MEM_SIZE) 
    {
        ANRI_DE debugPrint("Allocator memory overflow!");

        return nullptr;
    }

    void* newPointer = (void *) (currentMemoryAddress + size);
    offset += size;

    debugPrint("Allocated %d bytes, current offset %d returned pointer %d", size, offset, newPointer);

    return newPointer;
}

void Allocator::resetMemory() 
{
    offset = 0;
}