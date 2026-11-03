#include "WindGenerator.h"

void WindGenerator::updateForce(Particle* particle, float dt)
{
    PX_UNUSED(dt);
    Vector3D pos = particle->getPosition();

    if (isInArea(pos))
    {
        Vector3D relativeVelocity = windVelocity - particle->getVelocity();

        particle->addForce(relativeVelocity * coefficient);
    }
}

bool WindGenerator::isInArea(Vector3D pos)
{
    return pos.x >= areaPosition.x && pos.x <= areaPosition.x + areaSize.x &&
        pos.y >= areaPosition.y &&pos.y <= areaPosition.y + areaSize.y &&
        pos.z >= areaPosition.z &&pos.z <= areaPosition.z + areaSize.z;
}
