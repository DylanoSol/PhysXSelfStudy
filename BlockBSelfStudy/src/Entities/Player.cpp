#include "Player.h"
#include "../physics/Physics.h"

Player::Player(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{
	m_physics = physics;
}



void Player::Update(float deltaTime)
{
	
}