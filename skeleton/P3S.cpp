#include "P3S.h"
#include <iostream>

P3S::P3S(std::string name): Scene(name),gravity(Vector3D(0, -10, 0)),weakGravity(Vector3D(0, -3, 0)),
    wind(Vector3D(5, 0, 0),    // vel del viento
        Vector3D(-10, 0, -5), // esquina de la zona
        Vector3D(20, 15, 10), // tam de la zona
        1.0f),
    tornado(0.05f, 0.0f,
        Vector3D(-10, 0, -5),
        Vector3D(20, 15, 10),
        1.0f)
{
}

void P3S::init()
{
    // no aplicar gravedad directa a este sistema ya q la gravedad llegara mediante los generadores
    systemGravity.setAcceleration(Vector3D(0, 0, 0));
    systemWeakGravity.setAcceleration(Vector3D(0, 0, 0));

    // particula 1: gravedad normal mediante fuerza
    Particle* p1 = new Particle(
        Vector3D(-7, 7, 0),
        Vector3D(0, 0, 0),
        Vector3D(0, 0, 0),
        1.0f, 15.0f);

    p1->setMass(2.0f);
    systemGravity.createParticle(p1);

    // particula 2: gravedad mas debil mediante fuerza
    Particle* p2 = new Particle(
        Vector3D(0, 7, 0),
        Vector3D(0, 0, 0),
        Vector3D(0, 0, 0),
        1.0f, 15.0f);

    p2->setMass(5.0f);
    systemWeakGravity.createParticle(p2);

    // particula 3: gravedad aplicada directamente como acc constante
    Particle* p3 = new Particle(
        Vector3D(7, 7, 0),
        Vector3D(0, 0, 0),
        Vector3D(0, 0, 0),
        1.0f, 15.0f);

    p3->setMass(2.0f);
    systemAcceleration.createParticle(p3);

    /*std::cout << "Particulas creadas en P3S" << std::endl;
    std::cout << "P1: " << p1->getPosition().x << std::endl;
    std::cout << "P2: " << p2->getPosition().x << std::endl;
    std::cout << "P3: " << p3->getPosition().x << std::endl;*/
}

void P3S::update(double dt)
{
    float time = dt;

    //Activar o desactivar los generadores de gravedad
    if (enableGravity)
    {
        systemGravity.applyForceGenerator(gravity, time);
        systemWeakGravity.applyForceGenerator(weakGravity, time);
    }

    // El viento puede afectar a los tres sistemas
    if (enableWind)
    {
        systemGravity.applyForceGenerator(wind, time);
        systemWeakGravity.applyForceGenerator(wind, time);
        systemAcceleration.applyForceGenerator(wind, time);
    }

    if (enableTornado)
    {
        systemGravity.applyForceGenerator(tornado, time);
        systemWeakGravity.applyForceGenerator(tornado, time);
        systemAcceleration.applyForceGenerator(tornado, time);
    }

    // Gravedad directa para el tercer sistema
    systemAcceleration.setAcceleration(Vector3D(0, -10, 0));

    // actualizar los tres sistemas
    systemGravity.update(time);
    systemWeakGravity.update(time);
    systemAcceleration.update(time);
}

void P3S::cleanup()
{
}

void P3S::keyPress(unsigned char key,const physx::PxTransform& camera)
{
    PX_UNUSED(camera);
    switch (key)
    {
    case 'g':
        enableGravity = !enableGravity;
        std::cout << "Gravedad: " << (enableGravity ? "Activada" : "Desactivada") << std::endl;
        break;

    case 'v':
        enableWind = !enableWind;
        std::cout << "Viento: " << (enableWind ? "Activado" : "Desactivado") << std::endl;
        break;

    case 't':
        enableTornado = !enableTornado;
        std::cout << "Tornado: "<< (enableTornado ? "Activado" : "Desactivado") << std::endl;
        break;
    }
}
