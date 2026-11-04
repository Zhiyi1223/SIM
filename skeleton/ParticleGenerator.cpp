#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3D pos,Vector3D minVel, Vector3D maxVel,float rate, float life)
    : position(pos), minVelocity(minVel), maxVelocity(maxVel),emissionRate(rate), lifeTime(life), accumulator(0),
    randomEngine(std::random_device{}()), emitting(true), positionVariation(0, 0, 0), particleRadius(0.2f), particleColor(1, 1, 1, 1)
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

        // Distribucion uniforme para la velocidad
        std::uniform_real_distribution<float> distX(minVelocity.x, maxVelocity.x);
        std::uniform_real_distribution<float> distY(minVelocity.y, maxVelocity.y);
        std::uniform_real_distribution<float> distZ(minVelocity.z, maxVelocity.z);

        Vector3D velocity(distX(randomEngine), distY(randomEngine), distZ(randomEngine));

        // Distribucion gausiana para la posicion
        float x = position.x;
        float y = position.y;
        float z = position.z;

        if (positionVariation.x > 0)
        {
            std::normal_distribution<float> posX(position.x, positionVariation.x);
            x = posX(randomEngine);
        }

        if (positionVariation.y > 0)
        {
            std::normal_distribution<float> posY(position.y, positionVariation.y);
            y = posY(randomEngine);
        }

        if (positionVariation.z > 0)
        {
            std::normal_distribution<float> posZ(position.z, positionVariation.z);
            z = posZ(randomEngine);
        }

        Vector3D particlePosition(x, y, z);

        Particle* p = new Particle(particlePosition,velocity,Vector3D(0, -10, 0),1.0f,lifeTime,particleRadius,particleColor);

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