#include "P2S.h"
#include <iostream>

P2S::P2S(std::string name): Scene(name),
    fountain(
        Vector3D(-5, 0, 0), //pos de la fuente
        Vector3D(-2, 8, -2), //vel min
        Vector3D(2, 12, 2), //vel max
        40, 3.0f), //particula por segundo
    chispas(
        Vector3D(0, 0, 0),
        Vector3D(-10, 3, -10),
        Vector3D(10, 12, 10),
        35, 1.5f),
    niebla(
        Vector3D(5, 0, 0),
        Vector3D(-1, -0.4f, -1),
        Vector3D(1, 0.9f, 1),
        20, 5.0f)
{
    fountain.setAppearance(0.15f, Vector4(0.2f, 0.6f, 1.0f, 1.0f));
    chispas.setAppearance(0.1f, Vector4(1.0f, 0.5f, 0.05f, 1.0f));
    niebla.setAppearance(0.08f, Vector4(0.7f, 0.8f, 0.9f, 0.5f));

    niebla.setPositionVariation(Vector3D(10, 3, 10));

    fountain.setEmitting(true);
    chispas.setEmitting(false);
    niebla.setEmitting(false);

}

void P2S::init()
{
}

void P2S::update(double dt)
{
    fountain.update(system, dt);
    chispas.update(system, dt);
    niebla.update(system, dt);

    system.update(static_cast<float>(dt));
}

void P2S::cleanup()
{
}

void P2S::keyPress(unsigned char key,
    const physx::PxTransform& camera)
{
    PX_UNUSED(camera);

    switch (key)
    {
    case 'F':
        fountain.setEmitting(true);
        chispas.setEmitting(false);
        niebla.setEmitting(false);
        std::cout << "Fuente activa" << std::endl;
        break;

    case 'C':
        fountain.setEmitting(false);
        chispas.setEmitting(true);
        niebla.setEmitting(false);
        std::cout << "Chispas activas" << std::endl;
        break;

    case 'N':
        fountain.setEmitting(false);
        chispas.setEmitting(false);
        niebla.setEmitting(true);
        std::cout << "Niebla activa" << std::endl;
        break;
    }
}