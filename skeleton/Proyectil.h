#pragma once
#include "Particle.h"

class Proyectil :
    public Particle
{

public: 
    Proyectil(Vector3D Pos, Vector3D Dir,float realVel, float simVel, float realMass,float realGravity = -9.81f);

    void integrateEulerSemiImplicit(double t) override;

private:
    float realMass;
    float simGravity;

    void calculateValues(float realVel, float simVel,float realGravity);
};
