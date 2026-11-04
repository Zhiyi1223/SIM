#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3D pos,Vector3D minVel, Vector3D maxVel,float rate, float life)
    : position(pos), minVelocity(minVel), maxVelocity(maxVel),emissionRate(rate), lifeTime(life), accumulator(0),
    randomEngine(std::random_device{}()), emitting(true), particleRadius(0.2f), particleColor(1, 1, 1, 1)
{
}

void ParticleGenerator::update(ParticleSystem& system, float dt)
{
    if (!emitting)
        return;

    accumulator += emissionRate * dt;

    while (accumulator >= 1.0f)
    {
        accumulator -= 1.0f;

        std::uniform_real_distribution<float> distX(minVelocity.x, maxVelocity.x);
        std::uniform_real_distribution<float> distY(minVelocity.y, maxVelocity.y);
        std::uniform_real_distribution<float> distZ(minVelocity.z, maxVelocity.z);

        // Variacion aleatoria de la pos inicial
        std::uniform_real_distribution<float> posX(-positionVariation.x, positionVariation.x);
        std::uniform_real_distribution<float> posY(-positionVariation.y, positionVariation.y);
        std::uniform_real_distribution<float> posZ(-positionVariation.z, positionVariation.z);

        Vector3D particlePosition(position.x + posX(randomEngine),position.y + posY(randomEngine),position.z + posZ(randomEngine));

        Vector3D velocity(distX(randomEngine),distY(randomEngine),distZ(randomEngine));

        Particle* p = new Particle(position, velocity, Vector3D(0, -10, 0),1.0f, lifeTime, particleRadius,particleColor);

        system.createParticle(p);
    }
}

void ParticleGenerator::setEmitting(bool value)
{
    emitting = value;
}

void ParticleGenerator::setPositionVariation(Vector3D variation)
{
    positionVariation = variation;
}
void ParticleGenerator::setAppearance(float radius, Vector4 color)
{
    particleRadius = radius;
    particleColor = color;
}