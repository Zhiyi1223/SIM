#pragma once
#include "ForceGenerator.h"
class GravityGenerator :
    public ForceGenerator
{
public:
    GravityGenerator(Vector3D gravity): gravity(gravity)
    {
    }

    void updateForce(Particle* particle, float dt) override;

private:
    Vector3D gravity;
};

