#ifndef ANRI_PARTICLE_H
#define ANRI_PARTICLE_H

#include <engine/math/Vec2.h>
#include <engine/graphics/RGBColor.h>

struct Particle 
{
    Vec2f position;
    Vec2f previousPosition;
    Vec2f velocity;
    Vec2f acceleration;
    RGBColor color;
    float lifespan;
};

#endif