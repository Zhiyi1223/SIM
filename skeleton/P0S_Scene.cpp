#include "P0S_Scene.h"
using namespace physx;

P0S_Scene::P0S_Scene(const std::string& name): Scene(name), m_sphere(nullptr)
{

}

void P0S_Scene::init() {
    /*physx::PxSphereGeometry sphereGeometry(3.0f);
    physx::PxShape* shape = CreateShape(sphereGeometry);
    m_sphere = new RenderItem(shape, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
    shape->release();*/

    Vector3D u(3.0f, 1.0f, 0.0f);
    Vector3D v(0.0f, 4.0f, 0.0f);
    Vector3D w = u.cross(v);

    Vector3D x = u.normalize()*5.0f;
    Vector3D y = v.normalize()*5.0f;
    Vector3D z = w.normalize()*5.0f;

    PxSphereGeometry sphere(0.9f);

    PxShape* shapeX = CreateShape(sphere);
    PxShape* shapeY = CreateShape(sphere);
    PxShape* shapeZ = CreateShape(sphere);

    m_transformX = PxTransform(x);
    m_transformY = PxTransform(y);
    m_transformZ = PxTransform(z);

    m_x = new RenderItem(shapeX, &m_transformX, Vector4(1.0f,0.0f, 0.0f, 1.0f));
    m_y = new RenderItem(shapeY, &m_transformY,Vector4(0.0f, 1.0f, 0.0f, 1.0f));
    m_z = new RenderItem(shapeZ,&m_transformZ,Vector4(0.0f,0.0f,1.0f,1.0f)
    );

    shapeX->release();
    shapeY->release();
    shapeZ->release();
}

void P0S_Scene::cleanup()
{
    /*if (m_sphere != nullptr)
    {
        m_sphere->release();
        m_sphere = nullptr;
    }*/

    if (m_x != nullptr)
    {
        m_x->release();
        m_x = nullptr;
    }
    if (m_y != nullptr)
    {
        m_y->release();
        m_y = nullptr;
    }
    if (m_z != nullptr)
    {
        m_z->release();
        m_z = nullptr;
    }
}

void P0S_Scene::update(double dt)
{
}

void P0S_Scene::keyPress(unsigned char key,const physx::PxTransform& cameraTransform)
{
}