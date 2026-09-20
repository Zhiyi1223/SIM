#include "P0S_Scene.h"

P0S_Scene::P0S_Scene(const std::string& name): Scene(name), m_sphere(nullptr)
{

}

void P0S_Scene::init() {
    physx::PxSphereGeometry sphereGeometry(3.0f);
    physx::PxShape* shape = CreateShape(sphereGeometry);

    m_sphere = new RenderItem(shape, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

    shape->release();
}

void P0S_Scene::cleanup()
{
    if (m_sphere != nullptr)
    {
        m_sphere->release();
        m_sphere = nullptr;
    }
}

void P0S_Scene::update(double dt)
{
}

void P0S_Scene::keyPress(unsigned char key,const physx::PxTransform& cameraTransform)
{
}