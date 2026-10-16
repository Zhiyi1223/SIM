#include "P2S.h"

P2S::P2S(std::string name): Scene(name),
    fountain(
        Vector3D(-5, 0, 0),
        Vector3D(-2, 4, -2),
        Vector3D(2, 7, 2),
        20, 3.0f),
    sparks(
        Vector3D(0, 0, 0),
        Vector3D(-5, 2, -5),
        Vector3D(5, 9, 5),
        35, 1.5f),
    mist(
        Vector3D(5, 0, 0),
        Vector3D(-1, -0.2f, -1),
        Vector3D(1, 0.8f, 1),
        12, 5.0f)
{
}

void P2S::init()
{
}

void P2S::update(double dt)
{
    fountain.update(system, dt);
    sparks.update(system, dt);
    mist.update(system, dt);

    system.update(static_cast<float>(dt));
}

void P2S::cleanup()
{
    // ParticleSystem destruye sus particulas automáticamente
}

void P2S::keyPress(unsigned char key,
    const physx::PxTransform& camera)
{
    PX_UNUSED(key);
    PX_UNUSED(camera);
}