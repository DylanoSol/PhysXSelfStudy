#include "Player.h"
#include "../physics/Physics.h"

Player::Player(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{
	m_physicsHandler = physics;

	m_physics = m_physicsHandler->GetPhysics(); 

	//Create material
	m_material = m_physics->createMaterial(0.2, 0.5, 0.8);

	//Create sphere physics object
	m_sphere = physx::PxCreateDynamic(*m_physics, physx::PxTransform(0.f, 1.f, 0.f), physx::PxSphereGeometry(10.f), *m_material, 0.001f);

	m_physicsHandler->AddToWorld(m_sphere);
}

void Player::SetSwing(const physx::PxVec3& vec)
{
	m_swingVector = vec; 
	m_ready = true; 
}

void Player::Update(float deltaTime)
{
	m_sleeping = m_sphere->isSleeping();

	if (m_ready) Swing(); 

	m_lockCountdown--; 
	if (m_lockCountdown == 0) m_lock = false;
	
}

void Player::Swing()
{
	//Apply force on the player object
	m_sphere->addForce(m_swingVector);

	AmountOfSwings++;
	m_ready = false; 

	//Set a countdown to unlock the next swing
	m_lockCountdown = 50;
}