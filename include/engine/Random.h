#ifndef ANRI_RANDOM_H
#define ANRI_RANDOM_H

#include <random>

class Random
{
    public:
        static Random& getInstance();

        Random(Random const&) = delete;
        Random(Random&&) = delete;

        int getRandomIntInRange(int min, int max);
        float getRandomFloatInRange(float min, float max);


    private:
        Random();
        virtual ~Random();

        static std::random_device   randomDevice;
        static std::mt19937         mtEngine;

};

#endif