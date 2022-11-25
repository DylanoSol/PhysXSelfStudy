#pragma once
#include "Entity.h"

class Physics; 
class Player :
    public Entity
{
public: 
    Player(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics);
    void Update(float deltaTime) override; 
    void SetSwing(const physx::PxVec3& vec);


    bool m_ready = false; 

private: 
    void Swing();

    Physics* m_physicsHandler = nullptr; 

    physx::PxPhysics* m_physics = nullptr; 

    physx::PxMaterial* m_material = nullptr;

    physx::PxRigidDynamic* m_sphere = nullptr;

    physx::PxVec3 m_swingVector; 

};

