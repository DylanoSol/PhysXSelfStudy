#include "Pendulum.h"
#include "../physics/Physics.h"

Pendulum::Pendulum(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{
	m_physicsHandler = physics;

	m_physics = m_physicsHandler->GetPhysics();

	//Create material
	m_material = m_physics->createMaterial(0.2, 0.5, 0.8);

}


