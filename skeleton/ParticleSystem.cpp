#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
    for (Particle* p : particles)
        delete p;

    particles.clear();
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

        // gravedad es igual para todas
        p->setAcc(Vector3D(0, -10, 0));
        p->integrateEulerSemiImplicit(dt);

        Vector3D pos = p->getPosition();

        // eliminar por tiempo de vida o por salir del espacio
        if (!p->isAlive() ||pos.y < -20 || pos.y > 30 ||pos.x < -30 || pos.x > 30 ||pos.z < -30 || pos.z > 30)
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
