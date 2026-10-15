#include "P12S.h"

void P12S::update(double dt)
{
    for (Proyectil* p : projectiles)
        p->integrateEulerSemiImplicit(dt);
}

void P12S:: cleanup() {
    for (Proyectil* p : projectiles) {
        delete p;
    }
}

void P12S::keyPress(unsigned char key,
    const physx::PxTransform& camera)
{
    float realVel = 0;
    float mass = 0;

    switch (key)
    {

    case 'p': //pistola
        realVel = 290.0f;
        mass = 0.1f;
        break;

    case 'c':
        realVel = 250.0f;
        mass = 15.0f;
        break;

    case 'f': //proyectil fuerte
        realVel = 1800.0f;
        mass = 40.0f;
        break;

    }

    if (realVel != 0)
    {
        Vector3D dir(camera.q.rotate(physx::PxVec3(0, 0, -1)));

            projectiles.push_back(new Proyectil(Vector3D(camera.p),dir,realVel,50.0f,mass));
    }
}
