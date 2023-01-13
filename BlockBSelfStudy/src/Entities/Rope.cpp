#include "Rope.h"
#include "../physics/Physics.h"

Rope::Rope(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{

	m_physicsHandler = physics;

	m_physics = m_physicsHandler->GetPhysics();

	//Initialize pvd extension for constraints. 
	PxInitExtensions(*m_physics, m_physicsHandler->m_pvd);

	//Create material
	m_material = m_physics->createMaterial(0.2, 0.5, 0.8);


	m_origin = physx::PxCreateStatic(*m_physics, physx::PxTransform(position.x, position.y, position.z), physx::PxBoxGeometry(scale.x, scale.y, scale.z), *m_material);


}

void Rope::Update(float deltaTime)
{

}


