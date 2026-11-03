#pragma once
#include "ForceGenerator.h"
class GravityGenerator :
    public ForceGenerator
{
public:
    GravityGenerator(Vector3D gravity): gravity(gravity)
    {
    }

    void updateForce(Particle* particle, float dt) override
    {
        PX_UNUSED(dt);
        particle->addForce(gravity * particle->getMass());
    }

private:
    Vector3D gravity;
};

