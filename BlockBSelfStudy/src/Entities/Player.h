#pragma once
#include "Entity.h"
class Player :
    public Entity
{
public: 
    Player(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale));
    void Update(float deltaTime) override; 

private: 

};

