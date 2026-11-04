#include "ExplosionGenerator.h"

#include <cmath>

ExplosionGenerator::ExplosionGenerator(Vector3D center, float R,float tau, float K): center(center), R(R), tau(tau), K(K), explosionTime(0.0f), active(false)
{
}

void ExplosionGenerator::beginExplosion()
{
    explosionTime = 0.0f;
    active = true;
}

void ExplosionGenerator::updateForce(Particle* particle, float dt)
{

    if (active)
    {
        // desde centro de la explosion hasta la particula
        Vector3D direction = particle->getPosition() - center;

        //distancia a la explosion
        float r = direction.magnitude();

        ///comprobar que esta dentro del radio y evitar dividir entre cer
        if (r < R && r > 0.0001f)
        {
            // fuerza disminuye con el tiempo
            float timeEffect = std::exp(-explosionTime / tau);

            // formula de la fuerza de la explosion
            Vector3D forceToApply =direction * (K / (r * r)) * timeEffect;

            particle->addForce(forceToApply);
        }
    }
}

void ExplosionGenerator::updateTime(float dt)
{
    if (active)
    {
        explosionTime += dt;

        if (explosionTime >= 4.0f * tau)
        {
            active = false;
        }
    }
}
