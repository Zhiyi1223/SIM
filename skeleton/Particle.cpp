#include "Particle.h"

using namespace physx;

Particle::Particle(Vector3 Pos, Vector3 Vel): vel(Vel), pose(PxTransform(Pos)), renderItem(nullptr)
{
    PxSphereGeometry sphereGeometry(0.5f);
    PxShape* shape = CreateShape(sphereGeometry);

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
    pose.p += PxVec3(vel) * t;//con physx::PxVec3() convierte vel a PxVec3
}
