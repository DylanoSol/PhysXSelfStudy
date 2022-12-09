#include "CompletionTrigger.h"
#include "../physics/Physics.h"

CompletionTrigger::CompletionTrigger(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{
	m_physicsHandler = physics;

	m_physics = m_physicsHandler->GetPhysics();

}

void CompletionTrigger::Update(float deltaTime)
{

}