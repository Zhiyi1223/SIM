#include "ParticleSystem.h"
#include "ForceGenerator.h"

ParticleSystem::ParticleSystem() : acceleration(0, -10, 0)
{
}

ParticleSystem::~ParticleSystem()
{
    for (Particle* p : particles)
        delete p;

    particles.clear();
    forceGenerators.clear();
}

void ParticleSystem::createParticle(Particle* p)
{
    particles.push_back(p);
}

void ParticleSystem::update(float dt)
{
    int i = 0;
    //Para quedarnos en la misma pos cuando eliminamos un elemento 
    // y avanzar unicamente cuando conservamos la particla
    while (i < particles.size())
    {
        Particle* p = particles[i];

        // Aplicar la aceleracion directa configurada en el sistema
        p->setAcc(acceleration);
        // Aplicar todos los generadores activos a esta particula
        for (ForceGenerator* generator : forceGenerators)
        {
            p->applyForceGenerator(*generator, dt);
        }

        p->integrateEulerSemiImplicit(dt);

        Vector3D pos = p->getPosition();

        // eliminar por tiempo de vida o por salir del espacio
        if (!p->isAlive() ||pos.y < -50 || pos.y > 30 ||pos.x < -30 || pos.x > 30 ||pos.z < -30 || pos.z > 30)
        {
            delete p;
            particles.erase(particles.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

void ParticleSystem::setAcceleration(Vector3D newAcceleration)
{
    acceleration = newAcceleration;
}

void ParticleSystem::addForceGenerator(ForceGenerator* generator)
{
    forceGenerators.push_back(generator);
}

void ParticleSystem::removeForceGenerator(ForceGenerator* generator)
{
    int i = 0;

    while (i < forceGenerators.size())
    {
        if (forceGenerators[i] == generator)
        {
            forceGenerators.erase(forceGenerators.begin() + i);
        }
        else
        {
            i++;
        }
    }
}