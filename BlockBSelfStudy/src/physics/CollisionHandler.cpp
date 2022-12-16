#include "CollisionHandler.h"
#include <vector>

void CollisionHandler::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
	for (physx::PxU32 i = 0; i < count; i++)
	{
		// ignore pairs when shapes have been deleted
		if (pairs[i].flags & (physx::PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER | physx::PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
			continue;

		if ((pairs[i].otherActor->getName() == "PlayerSphere") && (pairs[i].triggerActor->getName() == "CompletionTrigger"))
		{
			printf("Level complete \n");
			
		}
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
    for (physx::PxU32 i = 0; i < nbPairs; i++)
    {
        const physx::PxContactPair& cp = pairs[i];

        if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            if (((pairHeader.actors[0]->getName() == "Bumper") &&
                (pairHeader.actors[1]->getName() == "PlayerSphere")) || ((pairHeader.actors[1]->getName() == "Bumper") &&
                (pairHeader.actors[0]->getName() == "PlayerSphere")))
            {
                printf("Piss \n");
            }
        }
    }
}

void CollisionHandler::onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count)
{

}
