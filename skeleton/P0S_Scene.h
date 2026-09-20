#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"

class P0S_Scene :
    public Scene
{
public:
    P0S_Scene(const std::string& name);

    void init() override;
    void cleanup() override;
    void update(double dt) override;
    void keyPress(unsigned char key,const physx::PxTransform& cameraTransform) override;
     
private:
    RenderItem* m_sphere;
};

