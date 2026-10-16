#pragma once
#include <vector>
#include "Particle.h"

//Guarda las particulas, actualiza movimiento y elimina las que ya no deben existir
class ParticleSystem
{
public:
    ParticleSystem();
    ~ParticleSystem();

    void createParticle(Particle* p);
    void update(float dt);

private:
    std::vector<Particle*> particles;
};

