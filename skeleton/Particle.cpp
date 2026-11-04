#include "Particle.h"
#include "ForceGenerator.h"

using namespace physx;

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Damping, float LifeTime, float Radius, Vector4 Color):
    vel(Vel), acc(Acc), damping(Damping), pose(PxTransform(Pos)), renderItem(nullptr), lifeTime(LifeTime), mass(1.0f), forceAcc(0, 0, 0)
{
    PxSphereGeometry sphere(0.5f);
    PxShape* shape = CreateShape(sphere);

    renderItem = new RenderItem(shape,&pose, Color);
    shape->release();
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