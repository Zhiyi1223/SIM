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
    fountain.setAppearance(0.7f, Vector4(0.2f, 0.6f, 1.0f, 1.0f));
    chispas.setAppearance(0.5f, Vector4(1.0f, 0.5f, 0.05f, 1.0f));
    niebla.setAppearance(0.2f, Vector4(0.7f, 0.8f, 0.9f, 0.5f));

    niebla.setPositionVariation(Vector3D(10, 3, 10));

}

void P2S::init()
{
    // Asignar los emisores al sistema de particulas
    system.addParticleGenerator(&fountain);
    system.addParticleGenerator(&chispas);
    system.addParticleGenerator(&niebla);

    fountain.setEmitting(true);
    chispas.setEmitting(false);
    niebla.setEmitting(false);

    system.activateParticleGenerator(&fountain);
}

void P2S::update(double dt)
{
    system.update(dt);
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
        enableFountain = !enableFountain;

        if (enableFountain)
            system.activateParticleGenerator(&fountain);
        else
            system.deactivateParticleGenerator(&fountain);

        break;

    case 'C':
        enableChispas = !enableChispas;

        if (enableChispas)
            system.activateParticleGenerator(&chispas);
        else
            system.deactivateParticleGenerator(&chispas);

        break;

    case 'N':
        enableNiebla = !enableNiebla;

        if (enableNiebla)
            system.activateParticleGenerator(&niebla);
        else
            system.deactivateParticleGenerator(&niebla);

        break;
    }
}