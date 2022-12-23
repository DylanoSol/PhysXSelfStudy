#include "Pendulum.h"
#include "../physics/Physics.h"

Pendulum::Pendulum(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{

	m_physicsHandler = physics;

	m_physics = m_physicsHandler->GetPhysics();
	PxInitExtensions(*m_physics, m_physicsHandler->m_pvd);

	//Create material
	m_material = m_physics->createMaterial(0.2, 0.5, 0.8);

	
	m_origin = physx::PxCreateStatic(*m_physics, physx::PxTransform(position.x, position.y + 100.f, position.z), physx::PxBoxGeometry(scale.x, scale.y, scale.z), *m_material);

	//Create thing that will rotate around origin
	m_hangingObject = physx::PxCreateDynamic(*m_physics, physx::PxTransform(position), physx::PxBoxGeometry(scale), *m_material, 100.f);
	
	//Configure joint
	m_joint = physx::PxRevoluteJointCreate(*m_physics, m_origin, physx::PxTransform(0.f, -50.f, 0.f), m_hangingObject, physx::PxTransform(0.f, 50.f, 0.f));
	m_joint->setLimit(physx::PxJointAngularLimitPair(physx::PxPi * -0.25f, physx::PxPi * 0.25f));
	m_joint->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eLIMIT_ENABLED, false);

	m_joint->setConstraintFlag(physx::PxConstraintFlag::eVISUALIZATION, true);

	m_joint->setDriveVelocity(0.4f);
	m_joint->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eDRIVE_ENABLED, true);

	m_physicsHandler->AddToWorld(m_hangingObject); 
	m_physicsHandler->AddToWorld(m_origin); 
}

void Pendulum::Update(float deltaTime)
{
//	m_hangingObject->addForce(physx::PxVec3(0.f, 0.f, 0.f)); 
}


