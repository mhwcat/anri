#ifndef ANRI_ALLOCATOR_H
#define ANRI_ALLOCATOR_H

#include <cstddef>

class Allocator 
{
    public:
        Allocator();
        virtual ~Allocator();

        static Allocator& getInstance();

        void* allocateMemory(std::size_t size);
        void resetMemory();

    private:
        void* startPointer;
        std::size_t offset;

        const std::size_t ALLOC_MEM_SIZE = 64 * 1024 * 1024;


};

#endif