#include "Player.h"


Player::Player(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale)) : Entity(position, rotation, scale)
{
	printf("testInit");
}



void Player::Update(float deltaTime)
{
	printf("testUpdate");
}