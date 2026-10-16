#pragma once
#include "Scene.h"
#include "ParticleGenerator.h"

//usar tecla 3
class P2S :
    public Scene
{
public:
    P2S(std::string name);

    void init() override;
    void update(double dt) override;
    void cleanup() override;
    void keyPress(unsigned char key,const physx::PxTransform& camera) override;

private:
    ParticleSystem system;
    ParticleGenerator fountain;
    ParticleGenerator sparks;
    ParticleGenerator mist;
};

