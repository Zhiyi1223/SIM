#pragma once
#include "WindGenerator.h"
class TornadoGenerator :
    public WindGenerator
{
public:
    TornadoGenerator(float strength, float centerPull,Vector3D areaPosition, Vector3D areaSize,float coefficient = 1.0f);

    virtual void updateForce(Particle* particle, float dt) override;

private:
    float strength;
    float centerPull;
};

