#pragma once
#include "RenderUtils.hpp"
#include"Vector3D.h"

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Damping);
	~Particle();

	void integrate(double t);

	void integrateEuler(double t);
	virtual void integrateEulerSemiImplicit(double t);
	void integrateVerlet(double t);

protected:
	Vector3 vel;
	physx::PxTransform pose; // a render item le pasaremos la direccion de este pose, para q se actualice automaticamente
	RenderItem* renderItem;

	Vector3D acc;//acceleracion
	float damping;
	physx::PxTransform posAnt;


	/*parctica 2:
	std::mt19937_mt;
	std::uniform_real_distribution<double> u(0,1)
	std::normal_distribution<double> g(0,1)
	g(_mt)*/

};

