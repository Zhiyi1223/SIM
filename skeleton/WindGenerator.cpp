#include "WindGenerator.h"

WindGenerator::WindGenerator(Vector3D windVelocity, Vector3D areaPosition,Vector3D areaSize, float k1, float k2)
    : windVelocity(windVelocity), areaPosition(areaPosition),areaSize(areaSize), k1(k1), k2(k2)
{
}

void WindGenerator::updateForce(Particle* particle, float dt)
{
    PX_UNUSED(dt);
    Vector3D pos = particle->getPosition();

    if (isInArea(pos))
    {
        // Diferencia entre la velocidad del viento y la particula
        Vector3D diff = windVelocity - particle->getVelocity();

        // Formula de la fuerza del viento
        Vector3D forceToApply =diff * k1 + diff * diff.magnitude() * k2;

        particle->addForce(forceToApply);
    }
}

bool WindGenerator::isInArea(Vector3D pos)
{
    return pos.x >= areaPosition.x && pos.x <= areaPosition.x + areaSize.x &&
        pos.y >= areaPosition.y &&pos.y <= areaPosition.y + areaSize.y &&
        pos.z >= areaPosition.z &&pos.z <= areaPosition.z + areaSize.z;
}
