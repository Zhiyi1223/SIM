#include "Proyectil.h"
#include <iostream>
#include <iomanip>

Proyectil::Proyectil(Vector3D Pos, Vector3D Dir,float realVel, float simVel, float mass, float gravity): Particle(Pos, Dir.normalize()* simVel,
		Vector3D(0, 0, 0), 1.0f, 10.0f),realMass(mass), simGravity(0)
{
	calculateValues(realVel, simVel, gravity);
}

void Proyectil::calculateValues(float realVel, float simVel,float realGravity)
{
    if (realVel > 0 && simVel > 0)
    {
        //justar la masa para conservar la energia
        float ratio = realVel / simVel;
        float simMass = realMass * ratio * ratio;

        setMass(simMass);

        //ajustar la gravedad para conservar la trayectoria
        float gravityRatio = simVel / realVel;
        simGravity = realGravity * gravityRatio * gravityRatio;

        // Mostrar los resultados
        std::cout << "\nNuevo proyectil\n";

        std::cout << "Velocidad real:" << realVel<< "\n";
        std::cout << "Velocidad simulada:" << simVel << "\n";

        std::cout << "Masa real: " << realMass << "\n";
        std::cout << "Masa simulada:" << getMass() << "\n";

        std::cout << "Gravedad real:" << realGravity << "\n";
        std::cout << "Gravedad simulada:" << simGravity << "\n";
    }
}
void Proyectil::integrateEulerSemiImplicit(double t) 
{ 
	acc = Vector3D(0, simGravity, 0); 
	Particle::integrateEulerSemiImplicit(t); 
}

