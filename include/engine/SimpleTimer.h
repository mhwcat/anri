#ifndef ANRI_SIMPLE_TIMER_H
#define ANRI_SIMPLE_TIMER_H

#include <chrono>

class SimpleTimer
{
    public:
        SimpleTimer();
        void start();

        long getMillisecondsSinceStart();
        long getMicrosecondsSinceStart();

    private:
        std::chrono::steady_clock::time_point begin;
};

#endif