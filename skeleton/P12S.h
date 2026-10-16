#pragma once
#include "Scene.h"
#include <vector>
#include "Proyectil.h"

//usar tecla 2
class P12S :
    public Scene
{
public:
    P12S(std::string name) : Scene(name) {}

    void init() override {}
    void update(double dt) override;
    void keyPress(unsigned char key,const physx::PxTransform& camera) override;
    void cleanup() override;

private:
    std::vector<Proyectil*> projectiles;
};

