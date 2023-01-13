#include "Rope.h"
#include "../physics/Physics.h"

Rope::Rope(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{

	//Hardcoded now just to test whether this works. 
	m_distance = new physx::PxVec3(2.f, 0.f, 0.f); 

	m_physicsHandler = physics;

	m_physics = m_physicsHandler->GetPhysics();

	//Initialize pvd extension for constraints. 
	PxInitExtensions(*m_physics, m_physicsHandler->m_pvd);

	//Create material
	m_material = m_physics->createMaterial(0.2, 0.5, 0.8);


	m_origin = physx::PxCreateStatic(*m_physics, physx::PxTransform(position.x, position.y, position.z), physx::PxBoxGeometry(scale.x, scale.y, scale.z), *m_material);

	for (int i = 0; i < m_amountOfBodyParts; i++)
	{
		m_body.push_back(physx::PxCreateDynamic(*m_physics, physx::PxTransform(physx::PxVec3(position.x + (m_distance->x * i), position.y + (m_distance->y * i), position.z + (m_distance->z * i))), physx::PxBoxGeometry(scale), *m_material, 10.f));
	}
	m_end = (physx::PxCreateDynamic(*m_physics, physx::PxTransform(physx::PxVec3(position.x + (m_distance->x * m_amountOfBodyParts), position.y + (m_distance->y * m_amountOfBodyParts), position.z + (m_distance->z * m_amountOfBodyParts))), physx::PxBoxGeometry(scale), *m_material, 10.f));


	//Configure joint
	m_joints.push_back(physx::PxSphericalJointCreate(*m_physics, m_origin, physx::PxTransform(physx::PxVec3(scale.x + (m_distance->x * 0.5f), scale.y + (m_distance->y * 0.5f), scale.z + (m_distance->z * 0.5f))), m_body[0], physx::PxTransform(scale.x + (m_distance->x - m_distance->x * 0.5f), scale.y + (m_distance->y - m_distance->y * 0.5f), scale.z + (m_distance->z - m_distance->z * 0.5f))));

	m_joints[0]->setConstraintFlag(physx::PxConstraintFlag::eVISUALIZATION, true);

	m_origin->setGlobalPose(physx::PxTransform(physx::PxVec3(position.x, position.y + 100, position.z), physx::PxQuat(0.5f * physx::PxPi, physx::PxVec3(0.f, 1.f, 0.f))));
	m_physicsHandler->AddToWorld(m_body[0]);
	m_physicsHandler->AddToWorld(m_origin);
}

void Rope::Update(float deltaTime)
{

}

void Rope::AddJoint(physx::PxRigidDynamic* bodyPart1, physx::PxRigidDynamic* bodyPart2, physx::PxSphericalJoint* joint)
{

}




