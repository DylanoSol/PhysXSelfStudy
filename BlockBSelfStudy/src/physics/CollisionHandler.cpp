#include "CollisionHandler.h"

void CollisionHandler::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
	for (physx::PxU32 i = 0; i < count; i++)
	{
		printf("response %d \n", i);
	}
}

void CollisionHandler::onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count)
{

}

void CollisionHandler::onWake(physx::PxActor** actors, physx::PxU32 count)
{

}

void CollisionHandler::onSleep(physx::PxActor** actors, physx::PxU32 count)
{

}

void CollisionHandler::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{

}

void CollisionHandler::onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count)
{

}
