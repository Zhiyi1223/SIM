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
