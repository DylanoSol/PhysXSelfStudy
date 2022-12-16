#include "CompletionTrigger.h"
#include "../physics/Physics.h"

CompletionTrigger::CompletionTrigger(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{
	m_physicsHandler = physics;

	m_physics = m_physicsHandler->GetPhysics();

	//Create material
	m_material = m_physics->createMaterial(0.2, 0.5, 0.8);

	m_triggerShape = m_physics->createShape(physx::PxBoxGeometry(scale.x, scale.y, scale.z), *m_material);
	
	m_triggerShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	m_triggerShape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);

	m_trigger = physx::PxCreateStatic(*m_physics, physx::PxTransform(position), *m_triggerShape); 

	m_trigger->setName("CompletionTrigger");

	m_physicsHandler->AddToWorld(m_trigger);

}

