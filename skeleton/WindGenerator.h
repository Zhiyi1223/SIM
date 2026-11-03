#pragma once
#include "ForceGenerator.h"
class WindGenerator :
    public ForceGenerator
{
public:
    WindGenerator(Vector3D windVelocity,Vector3D areaPosition, Vector3D areaSize,float coefficient = 1.0f): windVelocity(windVelocity),
        areaPosition(areaPosition),areaSize(areaSize),coefficient(coefficient)
    {
    }

    void updateForce(Particle* particle, float dt) override;

protected:
    Vector3D windVelocity;
    Vector3D areaPosition;
    Vector3D areaSize;
    float coefficient;

    bool isInArea(Vector3D pos);
};

