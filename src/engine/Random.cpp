#include <engine/Random.h>
#include <random>

std::random_device   Random::randomDevice;
std::mt19937         Random::mtEngine(Random::randomDevice());

Random::Random()
{

}

Random::~Random()
{

}

Random& Random::getInstance()
{
    static Random instance;

    return instance;
}

int Random::getRandomIntInRange(int min, int max)
{
    std::uniform_int_distribution<> distr(min, max);

    return distr(mtEngine);
}

float Random::getRandomFloatInRange(float min, float max)
{
    return 0.f;
}