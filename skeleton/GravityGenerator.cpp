#include "GravityGenerator.h"

void GravityGenerator::updateForce(Particle* particle, float dt)
{
    PX_UNUSED(dt);
    particle->addForce(gravity * particle->getMass());
}
