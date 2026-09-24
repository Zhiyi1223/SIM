#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"

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

    RenderItem* m_x;
    RenderItem* m_y;
    RenderItem* m_z;

    //guardar transformaciones para poder aplicarlos en variables locales
    physx::PxTransform m_transformX;
    physx::PxTransform m_transformY;
    physx::PxTransform m_transformZ;
};

