#include <engine/graphics/ParticleSystem.h>
#include <algorithm>
#include <ctime>
#include <engine/Random.h>
#include <engine/DebugPrint.h>


ParticleSystem::ParticleSystem(Vec2f _originPosition, Vec2f _originSize, uint32_t _maxParticleCount, float _maxTimeRunning, float _minLifespan, float _maxLifespan, Vec2f _additionalAcceleration, Vec2f _minVariation, Vec2f _maxVariation)
{
    originPosition = _originPosition;
    originSize = _originSize;
    maxParticleCount = _maxParticleCount;
    maxTimeRunning = _maxTimeRunning;
    minLifespan = _minLifespan;
    maxLifespan = _maxLifespan;
    additionalAcceleration = _additionalAcceleration;
    minVariation = _minVariation;
    maxVariation = _maxVariation;
    running = false;

    particles.reserve(maxParticleCount);
}

ParticleSystem::~ParticleSystem() 
{
    stop();
}

void ParticleSystem::start() 
{
    running = true;
    timeElapsed = 0.f;
}

void ParticleSystem::stop() 
{
    running = false;
}

void ParticleSystem::update(float deltaTime)
{
    timeElapsed += deltaTime;

    // Remove all particles with lifespan <= 0
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](Particle p) { return p.lifespan <= 0.f; }), particles.end());

    // Add particles
    if(running)
    {
        while(particles.size() < maxParticleCount)
        {
            Particle p = Particle {
                Vec2f{originPosition.x + Random::getInstance().getRandomFloatInRange(-originSize.x, originSize.x), originPosition.y + Random::getInstance().getRandomFloatInRange(-originSize.y, originSize.y)}, 
                Vec2f{0.f, 0.f}, 
                Vec2f{0.f, 0.f}, 
                Vec2f{Random::getInstance().getRandomFloatInRange(-10.f, 10.f), Random::getInstance().getRandomFloatInRange(-10.f, 10.f)}, 
                RGBColor{(unsigned char) Random::getInstance().getRandomIntInRange(160, 255), (unsigned char) Random::getInstance().getRandomIntInRange(23, 134), (unsigned char) Random::getInstance().getRandomIntInRange(0, 10), (unsigned char) 255},
                Random::getInstance().getRandomFloatInRange(minLifespan, maxLifespan)};
            particles.push_back(p);
        }
    }

    // Update particles positions and reduce lifespan
    for(auto &particle : particles)
    {
        // Movement variation
        float variationX = Random::getInstance().getRandomFloatInRange(minVariation.x, maxVariation.x);
        float variationY = Random::getInstance().getRandomFloatInRange(minVariation.y, maxVariation.y);

        particle.velocity.x += (particle.acceleration.x + additionalAcceleration.x + variationX) * deltaTime;
        particle.velocity.y += (particle.acceleration.y + additionalAcceleration.y + variationY) * deltaTime;

        particle.previousPosition.x = particle.position.x;
        particle.previousPosition.y = particle.position.y;
        particle.position.x = particle.position.x + (particle.velocity.x * deltaTime);
        particle.position.y = particle.position.y + (particle.velocity.y * deltaTime);

        particle.lifespan -= 1.f;


       // debugPrint("Particle {originPosition [%.3f, %.3f], acceleration [%.3f, %.3f], velocity [%.3f, %.3f] color [%d, %d, %d], lifespan [%.3f]}", particle.position.x, particle.position.y, particle.acceleration.x, particle.acceleration.y, particle.velocity.x, particle.velocity.y, particle.color.r, particle.color.g, particle.color.b, particle.lifespan);

    }

    if(maxTimeRunning > 0.f && timeElapsed >= maxTimeRunning)
    {
        stop();
    }
}

void ParticleSystem::draw(SDL_Renderer *renderer, float interp) 
{
    for(auto const& particle : particles)
    {
        // Interpolation for rendering
        float drawX = (particle.previousPosition.x * interp) + (particle.position.x * (1.f - interp));
        float drawY = (particle.previousPosition.y * interp) + (particle.position.y * (1.f - interp));

        SDL_Rect rect { (int) round(drawX),(int) round(drawY), 1, 1 };

        SDL_SetRenderDrawColor(renderer, particle.color.r, particle.color.g, particle.color.b, particle.color.alpha);
        SDL_RenderFillRect(renderer, &rect);
    }
}

/* Builder */

ParticleSystemBuilder& ParticleSystemBuilder::setOriginPosition(Vec2f _originPosition)
{
    this->originPosition = _originPosition;
    return *this;
}

ParticleSystemBuilder& ParticleSystemBuilder::setOriginSize(Vec2f _originSize)
{
    this->originSize = _originSize;
    return *this;
}

ParticleSystemBuilder& ParticleSystemBuilder::setMaxParticleCount(uint32_t _maxParticleCount)
{
    this->maxParticleCount = _maxParticleCount;
    return *this;
}

ParticleSystemBuilder& ParticleSystemBuilder::setMaxTimeRunning(float _maxTimeRunning)
{
    this->maxTimeRunning = _maxTimeRunning;
    return *this;
}

ParticleSystemBuilder& ParticleSystemBuilder::setLifespan(float _minLifespan, float _maxLifespan)
{
    this->minLifespan = _minLifespan;
    this->maxLifespan = _maxLifespan;
    return *this;
}

ParticleSystemBuilder& ParticleSystemBuilder::applyAdditionalAcceleration(Vec2f _acceleration)
{
    this->additionalAcceleration = _acceleration;
    return *this;
}

ParticleSystemBuilder& ParticleSystemBuilder::setVariation(Vec2f _minVariation, Vec2f _maxVariation)
{
    this->minVariation = _minVariation;
    this->maxVariation = _maxVariation;
    return *this;
}

std::unique_ptr<ParticleSystem> ParticleSystemBuilder::build()
{
    std::unique_ptr<ParticleSystem> ps = std::make_unique<ParticleSystem>(
        this->originPosition,
        this->originSize,
        this->maxParticleCount,
        this->maxTimeRunning,
        this->minLifespan,
        this->maxLifespan,
        this->additionalAcceleration,
        this->minVariation,
        this->maxVariation
    );

    return std::move(ps);
}


