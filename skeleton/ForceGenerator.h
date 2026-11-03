#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
	virtual void updateForce(Particle* particle, float dt) = 0; //cada tipo de fuerza calcula una fuerza distinta
	virtual ~ForceGenerator() = default;
};

