#pragma once
#include <vector>
#include "Particle.h"

class ForceGenerator;

//Guarda las particulas, actualiza movimiento y elimina las que ya no deben existir
class ParticleSystem
{
public:
    ParticleSystem();
    ~ParticleSystem();

    void createParticle(Particle* p);
    void update(float dt);

    //p3
    void applyForceGenerator(ForceGenerator& generator, float dt);
    void setAcceleration(Vector3D acceleration);

private:
    std::vector<Particle*> particles;

    //p3
    Vector3D acceleration;
};

