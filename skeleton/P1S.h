#pragma once
#include "Scene.h"
#include "Particle.h"
#include "Proyectil.h"

class P1S :
    public Scene
{
public:
    P1S(const std::string& name) : Scene(name) {}

    void init() override;
    void cleanup() override;
    void update(double dt) override;
    void keyPress(unsigned char key,const physx::PxTransform& cameraTransform) override;

private:
    Particle* mParticle = nullptr;
    int mIntegrator = 0;

    std::vector<Proyectil*> projectiles;

};

