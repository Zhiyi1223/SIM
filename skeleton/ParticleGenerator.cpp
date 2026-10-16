#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3D pos,Vector3D minVel, Vector3D maxVel,float rate, float life)
    : position(pos), minVelocity(minVel), maxVelocity(maxVel),emissionRate(rate), lifeTime(life), accumulator(0),
    randomEngine(std::random_device{}())
{
}

void ParticleGenerator::update(ParticleSystem& system, float dt)
{
    accumulator += emissionRate * dt;

    while (accumulator >= 1.0f)
    {
        accumulator -= 1.0f;

        std::uniform_real_distribution<float> distX(minVelocity.x, maxVelocity.x);
        std::uniform_real_distribution<float> distY(minVelocity.y, maxVelocity.y);
        std::uniform_real_distribution<float> distZ(minVelocity.z, maxVelocity.z);

        Vector3D velocity(distX(randomEngine),distY(randomEngine),distZ(randomEngine));

        Particle* p = new Particle(position, velocity, Vector3D(0, -10, 0),1.0f, lifeTime);

        system.createParticle(p);
    }
}
