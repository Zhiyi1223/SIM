#include "ParticleSystem.h"
#include "ForceGenerator.h"
#include "ParticleGenerator.h"

ParticleSystem::ParticleSystem() : acceleration(0, -10, 0)
{
}

ParticleSystem::~ParticleSystem()
{
    for (Particle* p : particles)
        delete p;

    particles.clear();
    forceGenerators.clear();
    particleGenerators.clear();
}

void ParticleSystem::createParticle(Particle* p)
{
    particles.push_back(p);
}

void ParticleSystem::update(float dt)
{
    //acctualizar los emisores asignados al sistema
    for (ParticleGenerator* generator : particleGenerators)
    {
        generator->update(*this, dt);
    }

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

void ParticleSystem::addParticleGenerator(ParticleGenerator* generator)
{
    bool found = false;
    int i = 0;

    while (i < particleGenerators.size() && !found)
    {
        if (particleGenerators[i] == generator)
            found = true;
        else
            i++;
    }

    if (!found)
    {
        particleGenerators.push_back(generator);
        generator->setEmitting(false);
    }
}

void ParticleSystem::activateParticleGenerator(ParticleGenerator* generator)
{
    int i = 0;
    bool found = false;

    while (i < particleGenerators.size() && !found)
    {
        if (particleGenerators[i] == generator)
        {
            generator->setEmitting(true);
            found = true;
        }
        else
            i++;
    }
}

void ParticleSystem::deactivateParticleGenerator(ParticleGenerator* generator)
{
    int i = 0;
    bool found = false;

    while (i < particleGenerators.size() && !found)
    {
        if (particleGenerators[i] == generator)
        {
            generator->setEmitting(false);
            found = true;
        }
        else
            i++;
    }
}