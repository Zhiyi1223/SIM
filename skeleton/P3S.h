#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ForceGenerator.h"
#include "WindGenerator.h"
#include "GravityGenerator.h"
#include "TornadoGenerator.h"
#include "ParticleGenerator.h"
#include "ExplosionGenerator.h"

//usar tecla 4
class P3S :
    public Scene
{
public:
    explicit P3S(std::string name);

    void init() override;
    void update(double dt) override;
    void cleanup() override;
    void keyPress(unsigned char key,const physx::PxTransform& camera) override;

private:
    ParticleSystem systemGravity;
    ParticleSystem systemWeakGravity;
    ParticleSystem systemAcceleration;
    ParticleSystem systemWind;

    ParticleGenerator emitter;

    ParticleSystem systemExplosion;
    ExplosionGenerator explosion;

    GravityGenerator gravity;
    GravityGenerator weakGravity;
    WindGenerator wind;
    TornadoGenerator tornado;

    bool enableGravity = true;
    bool enableWind = false;
    bool enableTornado = false;
};

