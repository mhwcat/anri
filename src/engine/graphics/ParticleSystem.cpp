#include <engine/graphics/ParticleSystem.h>
#include <algorithm>
#include <ctime>
#include <engine/Random.h>


ParticleSystem::ParticleSystem(Vec2 _originPosition, uint32_t _maxParticleCount, float _minLifespan, float _maxLifespan, bool _applyGravity)
{
    originPosition = _originPosition;
    maxParticleCount = _maxParticleCount;
    minLifespan = _minLifespan;
    maxLifespan = _maxLifespan;
    applyGravity = _applyGravity;
    running = false;
    timeElapsed = 0;

    particles.reserve(maxParticleCount);
}

ParticleSystem::~ParticleSystem() 
{
    stop();
}

void ParticleSystem::start() 
{
    running = true;
}

void ParticleSystem::stop() 
{
    running = false;
}

void ParticleSystem::update(float deltaTime)
{
    timeElapsed += deltaTime;

    float gravity = (applyGravity ? Y_ACCELERATION_GRAVITY : 0.f);

    // Remove all particles with lifespan <= 0
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](Particle p) { return p.lifespan <= 0.f; }), particles.end());

    // Add particles
    if(running)
    {
        while(particles.size() < maxParticleCount)
        {
            particles.push_back(Particle {
                Vec2{originPosition.x + Random::getInstance().getRandomIntInRange(-10, 10), originPosition.y + Random::getInstance().getRandomIntInRange(-10, 10)}, 
                Vec2{0.f, 0.f}, 
                Vec2{0.f, 0.f}, 
                Vec2{Random::getInstance().getRandomIntInRange(-100, 100), Random::getInstance().getRandomIntInRange(-100, 100)}, 
                Random::getInstance().getRandomIntInRange(100, 200)});
        }
    }

    // Update particles positions and reduce lifespan
    for(auto &particle : particles)
    {
        particle.velocity.x += particle.acceleration.x * deltaTime;
        particle.velocity.y += (particle.acceleration.y + gravity) * deltaTime;

        particle.previousPosition.x = particle.position.x;
        particle.previousPosition.y = particle.position.y;
        particle.position.x = particle.position.x + (particle.velocity.x * deltaTime);
        particle.position.y = particle.position.y + (particle.velocity.y * deltaTime);

        particle.lifespan -= 1.f;
    }
}

void ParticleSystem::draw(SDL_Renderer *renderer, float interp) 
{
    for(auto const& particle : particles)
    {
        // Interpolation for rendering
        float drawX = (particle.previousPosition.x * interp) + (particle.position.x * (1.f - interp));
        float drawY = (particle.previousPosition.y * interp) + (particle.position.y * (1.f - interp));

        SDL_Rect rect { (int) round(drawX),(int) round(drawY), 5, 5 };

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

