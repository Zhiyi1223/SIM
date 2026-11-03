#pragma once
#include "RenderUtils.hpp"
#include"Vector3D.h"

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Damping, float LifeTime = 2.0f, float Radius = 0.2f, Vector4 Color = { 1, 1, 1, 1 });
	~Particle();

	void integrate(double t);

	void integrateEuler(double t);
	virtual void integrateEulerSemiImplicit(double t);
	void integrateVerlet(double t);

	//Practica 2. Tiempo que le queda a cada particula y consultar pos
	void setAcc(Vector3D newAcc);
	bool isAlive() const;
	Vector3D getPosition() const;
	Vector3D getVelocity() const;

	//p3
	float getMass() const;
	void setMass(float m);

	void addForce(Vector3D force);
	void clearForces();

private:
	float lifeTime;

	//p3
	float mass;
	Vector3D forceAcc;

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

