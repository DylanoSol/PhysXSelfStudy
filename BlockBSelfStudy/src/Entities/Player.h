#pragma once
#include "Entity.h"

enum class PlayerStates { Waiting, Moving };
class Physics; 
class Player :
    public Entity
{
public: 
    Player(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics);
    void Update(float deltaTime) override; 
    void SetSwing(const physx::PxVec3& vec);
    void Launch(const physx::PxVec3& vec);

    void AddEnvironmentalForce(const physx::PxVec3& vec);

    int AmountOfSwings = 0; 
    
    bool m_ready = false; 

    bool m_lock = false; 

    bool m_sleeping = false; 

    PlayerStates m_playerState = PlayerStates::Waiting; 

private: 
    int m_lockCountdown = -1;

    void Swing();

    Physics* m_physicsHandler = nullptr; 

    physx::PxPhysics* m_physics = nullptr; 

    physx::PxMaterial* m_material = nullptr;

    physx::PxRigidDynamic* m_sphere = nullptr;

    physx::PxVec3 m_swingVector; 

    physx::PxVec3 m_environmentalForceVector = physx::PxVec3(0.f);

};

