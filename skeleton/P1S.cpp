#include "P1S.h"
#include <iostream>

using namespace physx;

void P1S::init()
{
    mParticle = new Particle(
        Vector3D(0.0f, 0.0f, 0.0f),  // pos
        Vector3D(0.0f, 5.0f, 0.0f),  // vel
        Vector3D(1.0f, 0.0f, 0.0f),  // acc
        0.99f                        // dampin
    );

    mIntegrator = 2;
}

void P1S::cleanup()
{
    delete mParticle;
    mParticle = nullptr;
}

void P1S::update(double dt)
{
    if (mParticle == nullptr)
        return;

    if (mIntegrator == 0)
        mParticle->integrate(dt);
    else if (mIntegrator == 1)
        mParticle->integrateEuler(dt);
    else if (mIntegrator == 2)
        mParticle->integrateEulerSemiImplicit(dt);
    else if (mIntegrator == 3)
        mParticle->integrateVerlet(dt);
}

void P1S::keyPress(unsigned char key,
    const PxTransform& cameraTransform)
{
    PX_UNUSED(cameraTransform);

    if (key == 'i')
    {
        mIntegrator = 0;
        std::cout << "Integrador normal" << std::endl;
    }
    else if (key == 'e')
    {
        mIntegrator = 1;
        std::cout << "Euler explicito" << std::endl;
    }
    else if (key == 's')
    {
        mIntegrator = 2;
        std::cout << "Euler semimplicito" << std::endl;
    }
    else if (key == 'v')
    {
        mIntegrator = 3;
        std::cout << "Verlet" << std::endl;
    }
}

