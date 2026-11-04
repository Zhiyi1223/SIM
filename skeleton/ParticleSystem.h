#pragma once
#include <vector>
#include "Particle.h"

class ForceGenerator;
class ParticleGenerator;
//Guarda las particulas, actualiza movimiento y elimina las que ya no deben existir
class ParticleSystem
{
public:
    ParticleSystem();
    ~ParticleSystem();

    void createParticle(Particle* p);
    void update(float dt);

    //p3
    void addForceGenerator(ForceGenerator* generator);
    void removeForceGenerator(ForceGenerator* generator);

    void setAcceleration(Vector3D acceleration);

private:
    std::vector<Particle*> particles;

    //p3
    std::vector<ForceGenerator*> forceGenerators;
    Vector3D acceleration;
};

