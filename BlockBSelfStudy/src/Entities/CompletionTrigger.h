#pragma once
#include "Entity.h"
class Physics;
class CompletionTrigger :
    public Entity
{
public:
    CompletionTrigger(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics);

private:
    Physics* m_physicsHandler = nullptr;

    physx::PxPhysics* m_physics = nullptr;

};

