#ifndef ANRI_PARTICLE_SYSTEM_H
#define ANRI_PARTICLE_SYSTEM_H

#include <vector>
#include <engine/graphics/Particle.h>
#include <engine/Config.h>
#include <SDL_rect.h>
#include <SDL_render.h>

class ParticleSystem 
{
    public:
        ParticleSystem(Vec2 _originPosition, uint32_t _maxParticleCount, float _minLifespan, float _maxLifespan, bool _applyGravity);
        virtual ~ParticleSystem();

        void start();
        void stop();

        void update(float deltaTime);
        void draw(SDL_Renderer *renderer, float interp);

    private:
        std::vector<Particle> particles;
        Vec2 originPosition;
        uint32_t maxParticleCount;
        float minLifespan;
        float maxLifespan;
        bool applyGravity;
        bool running;

        uint32_t timeElapsed;

        const float Y_ACCELERATION_GRAVITY = (float) Config::getInstance().getIntValueByKey("physics.gravity");


};



#endif