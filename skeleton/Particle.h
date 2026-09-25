#pragma once
#include "RenderUtils.hpp"
#include"Vector3D.h"

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	~Particle();

	void integrate(double t);

private:
	Vector3 vel;
	physx::PxTransform pose; // a render item le pasaremos la direccion de este pose, para q se actualice automaticamente
	RenderItem* renderItem;
};

