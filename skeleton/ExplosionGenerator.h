#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator :
    public ForceGenerator
{
public:
    ExplosionGenerator(Vector3D center, float R, float tau, float K);
    void updateForce(Particle* particle, float dt) override;

    void beginExplosion();
    void updateTime(float dt);

private:
    Vector3D center;
    float R;
    float tau;
    float K;

    float explosionTime;
    bool active;
};

