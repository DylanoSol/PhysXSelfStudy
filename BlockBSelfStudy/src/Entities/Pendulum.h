#pragma once
#include "Entity.h"
class Physics;
class Pendulum :
    public Entity
{
public:
    Pendulum(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics);

private:
    Physics* m_physicsHandler = nullptr;

    physx::PxPhysics* m_physics = nullptr;

    physx::PxRigidStatic* m_origin = nullptr;
    physx::PxRigidDynamic* m_hangingObject = nullptr; 

    physx::PxMaterial* m_material = nullptr;

};

