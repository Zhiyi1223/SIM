#include "DemoWind.h"
#include <iostream>

DemoWind::DemoWind(std::string name)
    : Scene(name),
    wind(
        Vector3D(10, 0, 0),// Viento hacia la derecha
        Vector3D(-1000, -1000, -1000), // Inicio de la zona
        Vector3D(2000, 2000, 2000),// Tamano de la zona
        10.0f, 0.0f) // Intensidad del viento
{
}

void DemoWind::init()
{
    enableWind = false;

    std::cout << "\n-DEMO-\n";
    std::cout << "P: Disparar proyectil\n";
    std::cout << "V: Activar/desactivar viento\n";
}

void DemoWind::update(double dt)
{
    int i = 0;

    while (i < projectiles.size())
    {
        Proyectil* p = projectiles[i];

        // Aplicar viento si esta activado
        if (enableWind)
        {
            p->applyForceGenerator(wind, dt);
        }

        p->integrateEulerSemiImplicit(dt);

        if (!p->isAlive())
        {
            delete p;
            projectiles.erase(projectiles.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

void DemoWind::cleanup()
{
    for (Proyectil* p : projectiles)
    {
        delete p;
    }

    projectiles.clear();
}

void DemoWind::keyPress(unsigned char key,
    const physx::PxTransform& camera)
{
    switch (key)
    {
    case 'P':
    {
        // proyectil sencillo
        float realVel = 290.0f;
        float simVel = 20.0f;
        float mass = 0.1f;

        Vector3D dir(camera.q.rotate(physx::PxVec3(0, 0, -1)));

        Proyectil* p = new Proyectil(Vector3D(camera.p),dir,realVel,simVel,mass);
        projectiles.push_back(p);
        std::cout << "Proyectil disparado" << std::endl;
        break;
    }

    case 'V':
        enableWind = !enableWind;

        std::cout << "Viento: "<< (enableWind ? "ACTIVADO" : "DESACTIVADO")<< std::endl;
        break;
    }
}