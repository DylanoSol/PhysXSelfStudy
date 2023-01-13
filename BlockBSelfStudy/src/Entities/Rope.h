#pragma once
#include "Entity.h"
#include <vector>

class Physics;
class Rope :
    public Entity
{
public:
    Rope(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics);
    void Update(float deltaTime) override;

private:
    Physics* m_physicsHandler = nullptr;

    physx::PxPhysics* m_physics = nullptr;

    physx::PxRigidStatic* m_origin = nullptr;

    physx::PxMaterial* m_material = nullptr;

 
};

