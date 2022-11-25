#pragma once

#include <PhysX/PxPhysicsAPI.h>
class Entity
{
public:
	Entity(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale));

	virtual ~Entity() { };
	virtual void Update(float deltaTime) { };

	physx::PxVec3 m_position; 
	physx::PxQuat m_rotation; 
	physx::PxVec3 m_scale; 
private: 


};

