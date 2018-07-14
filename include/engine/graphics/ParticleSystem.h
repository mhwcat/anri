#ifndef ANRI_PARTICLE_SYSTEM_H
#define ANRI_PARTICLE_SYSTEM_H


#include <engine/graphics/Particle.h>
#include <engine/Config.h>
#include <vector>
#include <memory>
#include <SDL_rect.h>
#include <SDL_render.h>

class ParticleSystem 
{
    public:
        ParticleSystem(Vec2 _originPosition, Vec2 _originSize, uint32_t _maxParticleCount, float _maxTimeRunning, float _minLifespan, float _maxLifespan, Vec2 _additionalAcceleration, Vec2 _minVariation, Vec2 _maxVariation);
        virtual ~ParticleSystem();

        void start();
        void stop();

        void update(float deltaTime);
        void draw(SDL_Renderer *renderer, float interp);

    private:
        std::vector<Particle> particles;
        Vec2 originPosition;
        Vec2 originSize;
        uint32_t maxParticleCount;
        float maxTimeRunning;
        float minLifespan;
        float maxLifespan;
        Vec2 additionalAcceleration;
        Vec2 minVariation;
        Vec2 maxVariation;
        bool running;

        float timeElapsed;

};

class ParticleSystemBuilder 
{
    private:
        Vec2 originPosition;
        Vec2 originSize;
        uint32_t maxParticleCount;
        float maxTimeRunning;
        float minLifespan;
        float maxLifespan;
        Vec2 additionalAcceleration;
        Vec2 minVariation;
        Vec2 maxVariation;

    public:
        ParticleSystemBuilder& setOriginPosition(Vec2 _originPosition);
        ParticleSystemBuilder& setOriginSize(Vec2 _originSize);
        ParticleSystemBuilder& setMaxParticleCount(uint32_t _maxParticleCount);
        ParticleSystemBuilder& setMaxTimeRunning(float _maxTimeRunning);
        ParticleSystemBuilder& setLifespan(float _minLifespan, float _maxLifespan);
        ParticleSystemBuilder& applyAdditionalAcceleration(Vec2 _acceleration);
        ParticleSystemBuilder& setVariation(Vec2 _minVariation, Vec2 _maxVariation);

        std::unique_ptr<ParticleSystem> build();
};



#endif