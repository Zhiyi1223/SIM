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

    void updateForce(Particle* particle, float dt) override
    {
        PX_UNUSED(dt);

        Vector3D pos = particle->getPosition();

        bool inside =
            pos.x >= areaPosition.x && pos.x <= areaPosition.x + areaSize.x &&
            pos.y >= areaPosition.y && pos.y <= areaPosition.y + areaSize.y &&
            pos.z >= areaPosition.z &&pos.z <= areaPosition.z + areaSize.z;

        if (inside)
        {
            Vector3D relativeVelocity = windVelocity - particle->getVelocity();

            particle->addForce(relativeVelocity * coefficient);
        }
    }

private:
    Vector3D windVelocity;
    Vector3D areaPosition;
    Vector3D areaSize;
    float coefficient;
};

