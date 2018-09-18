#ifndef ANRI_PARTICLE_SYSTEM_H
#define ANRI_PARTICLE_SYSTEM_H


#include <engine/graphics/Particle.h>
#include <engine/Config.h>
#include <engine/math/Vec2.h>
#include <vector>
#include <memory>
#include <SDL_rect.h>
#include <SDL_render.h>

class ParticleSystem 
{
    public:
        ParticleSystem(Vec2f _originPosition, Vec2f _originSize, uint32_t _maxParticleCount, float _maxTimeRunning, float _minLifespan, float _maxLifespan, Vec2f _additionalAcceleration, Vec2f _minVariation, Vec2f _maxVariation);
        virtual ~ParticleSystem();

        void start();
        void stop();

        void update(float deltaTime);
        void draw(SDL_Renderer *renderer, float interp);

    private:
        std::vector<Particle> particles;
        Vec2f originPosition;
        Vec2f originSize;
        uint32_t maxParticleCount;
        float maxTimeRunning;
        float minLifespan;
        float maxLifespan;
        Vec2f additionalAcceleration;
        Vec2f minVariation;
        Vec2f maxVariation;
        bool running;

        float timeElapsed;

};

class ParticleSystemBuilder 
{
    private:
        Vec2f originPosition;
        Vec2f originSize;
        uint32_t maxParticleCount;
        float maxTimeRunning;
        float minLifespan;
        float maxLifespan;
        Vec2f additionalAcceleration;
        Vec2f minVariation;
        Vec2f maxVariation;

    public:
        ParticleSystemBuilder& setOriginPosition(Vec2f _originPosition);
        ParticleSystemBuilder& setOriginSize(Vec2f _originSize);
        ParticleSystemBuilder& setMaxParticleCount(uint32_t _maxParticleCount);
        ParticleSystemBuilder& setMaxTimeRunning(float _maxTimeRunning);
        ParticleSystemBuilder& setLifespan(float _minLifespan, float _maxLifespan);
        ParticleSystemBuilder& applyAdditionalAcceleration(Vec2f _acceleration);
        ParticleSystemBuilder& setVariation(Vec2f _minVariation, Vec2f _maxVariation);

        std::unique_ptr<ParticleSystem> build();
};



#endif