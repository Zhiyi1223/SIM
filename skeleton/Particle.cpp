#include "Particle.h"
#include "ForceGenerator.h"

using namespace physx;

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc,float Damping, float LifeTime, float Radius, Vector4 Color,bool createRenderItem)
    : vel(Vel), acc(Acc), damping(Damping),pose(PxTransform(Pos)), renderItem(nullptr),lifeTime(LifeTime), mass(1.0f), forceAcc(0, 0, 0),
    radius(Radius), color(Color)
{
    if (createRenderItem)
    {
        PxSphereGeometry sphere(radius);
        PxShape* shape = CreateShape(sphere);

        if (shape != nullptr)
        {
            renderItem = new RenderItem(shape, &pose, color);
            shape->release();
        }
    }
}

Particle::~Particle()
{
    if (renderItem != nullptr)
    {
        renderItem->release();
        renderItem = nullptr;
    }
}


void Particle::integrate(double t)
{
    vel += acc * t;
    vel = vel * std::pow(damping, t);

    //euler: pos nueva = pos actual + velocidad × tiempo
    pose.p += PxVec3(vel) * t;//con physx::PxVec3() convierte vel a PxVec3
}

void Particle::integrateEuler(double t)
{
    //actualizar posicion
    pose.p += PxVec3(vel) * t;
    //y velocidad
    vel += acc * t;
    //aplicar damping
    vel = vel * std::pow(damping, t);

    acc = 0;
}

void Particle::integrateEulerSemiImplicit(double t)
{
    //restar tiempo transcurrido, tiempo de vida disminuye independientemente del movimiento
    lifeTime -= static_cast<float>(t);

    Vector3D finalAcc = acc + forceAcc * (1.0f / mass);

    //actualizar velocidad
    //vel += acc * t;
    vel += finalAcc * t;
    //aplicar damping
    vel = vel * std::pow(damping, t);
    
    //despues actualizar posicion
    pose.p += PxVec3(vel) * t;

    clearForces();
    acc = 0;
}

void Particle::integrateVerlet(double t) 
{
    PxTransform posTemp = posAnt;
    posAnt = pose;
    //
    pose.p = 2 * posAnt.p - posTemp.p + physx::PxVec3(acc) * t*t;

    acc = 0;
}

void Particle::setAcc(Vector3D newAcc)
{
    acc = newAcc;
}

bool Particle::isAlive() const
{
    return lifeTime > 0;
}

Vector3D Particle::getPosition() const
{
    return Vector3D(pose.p);
}

Vector3D Particle::getVelocity() const
{
    return vel;
}

float Particle::getMass() const
{
    return mass;
}

void Particle::setMass(float m)
{
    if (m > 0)
        mass = m;
}

void Particle::addForce(Vector3D force)
{
    forceAcc += force;
}

void Particle::clearForces()
{
    forceAcc = Vector3D(0, 0, 0);
}


void Particle::applyForceGenerator(ForceGenerator& generator, float dt)
{
    generator.updateForce(this, dt);
}

void Particle::setAppearance(float newRadius, Vector4 newColor)
{
    radius = newRadius;
    color = newColor;
}

Particle* Particle::clone(Vector3D newPosition, Vector3D newVelocity) const
{
    Particle* p = new Particle(newPosition,newVelocity,acc,damping,lifeTime,radius,color);
    p->setMass(mass);

    return p;
}