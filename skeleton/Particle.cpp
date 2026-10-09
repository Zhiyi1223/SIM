#include "Particle.h"

using namespace physx;

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Damping): vel(Vel), acc(Acc), damping(Damping), pose(PxTransform(Pos)), renderItem(nullptr)
{
    PxSphereGeometry sphere(1.0f);
    PxShape* shape = CreateShape(sphere);

    renderItem = new RenderItem(shape,&pose,Vector4(1.0f, 0.0f, 0.0f, 1.0f));

    shape->release();
}

Particle::~Particle()
{
    if (renderItem != nullptr)
    {
        renderItem->release();
        renderItem = nullptr;
    }
}


void Particle::integrate(double t)
{
    vel += acc * t;
    vel = vel * std::pow(damping, t);

    //euler: pos nueva = pos actual + velocidad × tiempo
    pose.p += PxVec3(vel) * t;//con physx::PxVec3() convierte vel a PxVec3
}

void Particle::integrateEuler(double t)
{
    //actualizar posicion
    pose.p += PxVec3(vel) * t;
    //y velocidad
    vel += acc * t;
    //aplicar damping
    vel = vel * std::pow(damping, t);

    acc = 0;
}

void Particle::integrateEulerSemiImplicit(double t)
{
    //actualizar velocidad
    vel += acc * t;
    //aplicar damping
    vel = vel * std::pow(damping, t);
    //despues actualizar posicion
    pose.p += PxVec3(vel) * t;

    acc = 0;
}

void Particle::integrateVerlet(double t) 
{
    PxTransform posTemp = posAnt;
    posAnt = pose;
    //
    pose.p = 2 * posAnt.p - posTemp.p + physx::PxVec3(acc) * t*t;

    acc = 0;
}