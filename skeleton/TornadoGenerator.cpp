#include "TornadoGenerator.h"
TornadoGenerator::TornadoGenerator(float strength, float centerPull,Vector3D areaPosition, Vector3D areaSize, float coefficient)
    : WindGenerator(Vector3D(0, 0, 0), areaPosition, areaSize, coefficient),strength(strength), centerPull(centerPull)
{
}

void TornadoGenerator::updateForce(Particle* particle, float dt)
{
    Vector3D pos = particle->getPosition();
    if (isInArea(pos))
    {
        // Centro de la zona del torbellino
        Vector3D center = areaPosition + areaSize * 0.5f;

        // Velocidad tangencial del torbellino
        Vector3D tornadoVelocity(-(pos.z - center.z),centerPull - (pos.y - center.y),pos.x - center.x);

        tornadoVelocity = tornadoVelocity * strength;

        // Fuerza según la diferencia de velocidades
        Vector3D relativeVelocity = tornadoVelocity - particle->getVelocity();

        particle->addForce(relativeVelocity * coefficient);
    }
}