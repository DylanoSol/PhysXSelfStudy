#pragma once
#include "Entity.h"

class Physics; 
class Player :
    public Entity
{
public: 
    Player(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics);
    void Update(float deltaTime) override; 

private: 
    Physics* m_physics = nullptr; 

};

