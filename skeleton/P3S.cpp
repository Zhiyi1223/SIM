#include "P3S.h"
#include <iostream>

P3S::P3S(std::string name): Scene(name), emitter(Vector3D(0, 7, 0),
    Vector3D(-2, 3, -2),
    Vector3D(2, 6, 2),
    20, 10.0f),
    gravity(Vector3D(0, -10, 0)),
    weakGravity(Vector3D(0, -3, 0)),

    wind(
    Vector3D(5, 0, 0),
    Vector3D(-10, 0, -5),
    Vector3D(20, 15, 10),
    1.0f, 0.0f),
    
    tornado(
    0.05f, 0.0f,
    Vector3D(-10, 0, -5),
    Vector3D(20, 15, 10),
    1.0f, 0.0f),

    explosion(Vector3D(0, 7, 0), 12.0f, 1.0f, 100000.0f)
{
    emitter.setAppearance(0.15f, Vector4(0.2f, 0.8f, 1.0f, 1.0f));
}

void P3S::init()
{
    enableGravity = false;
    enableWind = false;
    enableTornado = false;

    // no aplicar gravedad directa a este sistema ya q la gravedad llegara mediante los generadores
    systemGravity.setAcceleration(Vector3D(0, 0, 0));
    systemWeakGravity.setAcceleration(Vector3D(0, 0, 0));

    systemAcceleration.setAcceleration(Vector3D(0, -10, 0));
    systemWind.setAcceleration(Vector3D(0, 0, 0));
    systemExplosion.setAcceleration(Vector3D(0, 0, 0));

    systemExplosion.addForceGenerator(&explosion);

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
        Vector3D(0, 7, 4),
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

    p3->setMass(3.0f);
    systemAcceleration.createParticle(p3);

    // particula independientes para probar la explosion
    Particle* p4 = new Particle(
        Vector3D(-3, 7, 0),
        Vector3D(0, 0, 0),
        Vector3D(0, 0, 0),
        1.0f, 15.0f);

    Particle* p5 = new Particle(
        Vector3D(3, 7, 0),
        Vector3D(0, 0, 0),
        Vector3D(0, 0, 0),
        1.0f, 15.0f);

    Particle* p6 = new Particle(
        Vector3D(0, 10, 3),
        Vector3D(0, 0, 0),
        Vector3D(0, 0, 0),
        1.0f, 15.0f);

    systemExplosion.createParticle(p4);
    systemExplosion.createParticle(p5);
    systemExplosion.createParticle(p6);
}

void P3S::update(double dt)
{
    float time = dt;

    // Generar nuevas particulas
    emitter.update(systemWind, time);

     // Cada sistema aplica automaticamente sus generadores registrados
    systemGravity.update(time);
    systemWeakGravity.update(time);
    systemAcceleration.update(time);
    systemWind.update(time);
    systemExplosion.update(time);

    // Actualizar el tiempo de la explosion una sola vez
    explosion.updateTime(time);
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

        if (enableGravity)
        {
            systemGravity.addForceGenerator(&gravity);
            systemWeakGravity.addForceGenerator(&weakGravity);
        }
        else
        {
            systemGravity.removeForceGenerator(&gravity);
            systemWeakGravity.removeForceGenerator(&weakGravity);
        }

        std::cout << "Gravedad: "<< (enableGravity ? "Activada" : "Desactivada")<< std::endl;
        break;

    case 'v':
        enableWind = !enableWind;

        if (enableWind)
        {
            systemWind.addForceGenerator(&wind);
        }
        else
        {
            systemWind.removeForceGenerator(&wind);
        }

        std::cout << "Viento: "<< (enableWind ? "Activado" : "Desactivado")<< std::endl;
        break;

    case 't':
        enableTornado = !enableTornado;

        if (enableTornado)
        {
            systemWind.addForceGenerator(&tornado);
        }
        else
        {
            systemWind.removeForceGenerator(&tornado);
        }

        std::cout << "Tornado: "<< (enableTornado ? "Activado" : "Desactivado")<< std::endl;
        break;

    case 'e':
        explosion.beginExplosion();
        std::cout << "BOOM!" << std::endl;
        break;
    }
}
