#include "Particle.h"

using namespace physx;

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc): vel(Vel), acc(Acc), pose(PxTransform(Pos)), renderItem(nullptr)
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

//euler: pos nueva = pos actual + velocidad × tiempo
void Particle::integrate(double t)
{
    vel += acc * t; //P1A2, primero la acc modifica la vel
    //despues cambiar la posicion
    pose.p += PxVec3(vel) * t;//con physx::PxVec3() convierte vel a PxVec3
}
