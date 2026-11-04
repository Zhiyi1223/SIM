#pragma once
#include "ForceGenerator.h"
class WindGenerator :
    public ForceGenerator
{
public:
    WindGenerator(Vector3D windVelocity, Vector3D areaPosition,Vector3D areaSize, float k1, float k2 = 0.0f);

    void updateForce(Particle* particle, float dt) override;

protected:
    Vector3D windVelocity;
    Vector3D areaPosition;
    Vector3D areaSize;
    float k1;
    float k2;

    bool isInArea(Vector3D pos);
};

