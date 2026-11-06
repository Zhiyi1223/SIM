#pragma once

#include "Scene.h"
#include <vector>
#include "Proyectil.h"
#include "WindGenerator.h"

// Escena demo del proyecto final
// P: disparar
// V: activar/desactivar viento

class DemoWind : public Scene
{
public:
    explicit DemoWind(std::string name);

    void init() override;
    void update(double dt) override;
    void cleanup() override;

    void keyPress(unsigned char key,const physx::PxTransform& camera) override;

private:
    std::vector<Proyectil*> projectiles;

    WindGenerator wind;
    bool enableWind = false;
};