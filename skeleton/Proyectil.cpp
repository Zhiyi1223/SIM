#include "Proyectil.h"

Proyectil::Proyectil(Vector3D Pos, Vector3D Dir, float realVel, float simVel, float mass) : 
	Particle(Pos, Dir.normalize()* simVel, Vector3D(0, 0, 0), 1.0f), realMass(mass), simGravity(0) 
{ 
	calculateValues(realVel, simVel); 
}

void Proyectil::calculateValues(float realVel, float simVel) 
{
	float ratio = realVel / simVel;
	simGravity = -9.81f / (ratio * ratio);
}

void Proyectil::integrateEulerSemiImplicit(double t) 
{ 
	acc = Vector3D(0, simGravity, 0); 
	Particle::integrateEulerSemiImplicit(t); 
}

