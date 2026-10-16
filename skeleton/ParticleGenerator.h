#pragma once
#include <random>
#include "ParticleSystem.h"

//cada emisor tendrá una posición fija, un intervalo mínimo y máximo para la velocidad en cada eje
//una frecuencia de emisión y un tiempo de vida.
class ParticleGenerator
{
public:
    ParticleGenerator(Vector3D pos, Vector3D minVel,
        Vector3D maxVel, float rate, float life);

    void update(ParticleSystem& system, float dt);

private:
    Vector3D position;
    Vector3D minVelocity;
    Vector3D maxVelocity;

    float emissionRate;
    float lifeTime;
    float accumulator;

    std::mt19937 randomEngine;
};

