#include "TornadoGenerator.h"
TornadoGenerator::TornadoGenerator(float K, float centerPull,Vector3D areaPosition, Vector3D areaSize, float k1, float k2)
    : WindGenerator(Vector3D(0, 0, 0), areaPosition,areaSize, k1, k2),K(K), centerPull(centerPull)
{
}

void TornadoGenerator::updateForce(Particle* particle, float dt)
{
    PX_UNUSED(dt);

    Vector3D pos = particle->getPosition();

    if (isInArea(pos))
    {
        //cento del volumen del tornado
        Vector3D center = areaPosition + areaSize * 0.5f;

        // Velocidad del torbellino segun la posicion
        Vector3D tornadoVelocity(-(pos.z - center.z),centerPull - (pos.y - center.y),pos.x - center.x);

        tornadoVelocity = tornadoVelocity * K;

        // diff entre la velocidad del torbellino y la particula
        Vector3D diff = tornadoVelocity - particle->getVelocity();

        // Formula de la fuerza del viento aplicada al torbellino
        Vector3D forceToApply =diff * k1 + diff * diff.magnitude() * k2;

        particle->addForce(forceToApply);
    }
}