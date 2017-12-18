#ifndef ANRI_SIMPLE_TIMER_H
#define ANRI_SIMPLE_TIMER_H

#include <chrono>

class SimpleTimer
{
    public:
        SimpleTimer();
        void start();

        uint64_t getMillisecondsSinceStart();
        uint64_t getMicrosecondsSinceStart();

    private:
        std::chrono::high_resolution_clock::time_point begin;
};

#endif