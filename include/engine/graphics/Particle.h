#ifndef ANRI_PARTICLE_H
#define ANRI_PARTICLE_H

#include <engine/math/Vec2.h>

struct Particle 
{
    Vec2 position;
    Vec2 previousPosition;
    Vec2 velocity;
    Vec2 acceleration;
    float lifespan;
};

#endif