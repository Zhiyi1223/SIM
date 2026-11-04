#pragma once
#include "WindGenerator.h"
class TornadoGenerator :
    public WindGenerator
{
public:
    TornadoGenerator(float K, float centerPull,Vector3D areaPosition, Vector3D areaSize,float k1, float k2 = 0.0f);

    void updateForce(Particle* particle, float dt) override;

private:
    float K;
    float centerPull;
};

