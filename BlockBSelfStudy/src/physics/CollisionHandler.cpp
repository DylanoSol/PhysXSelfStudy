#include "CollisionHandler.h"
#include <vector>
#include "../Entities/Entity.h"
#include "../Entities/Bumper.h"
#include "../Entities/Player.h"

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
            //Bumper - Player collision response
            if (((pairHeader.actors[0]->getName() == "Bumper") &&
                (pairHeader.actors[1]->getName() == "PlayerSphere")) || ((pairHeader.actors[1]->getName() == "Bumper") &&
                (pairHeader.actors[0]->getName() == "PlayerSphere")))
            {
                printf("Piss \n");
                physx::PxActor* player = nullptr;
                physx::PxActor* bumper = nullptr;

                //Get which one is which
                if (pairHeader.actors[0]->getName() == "PlayerSphere")
                {
                    player = pairHeader.actors[0];
                    bumper = pairHeader.actors[1];
                }
                else
                {
                    bumper = pairHeader.actors[0];
                    player = pairHeader.actors[1];
                }

                //Casst into entities
                Player* playerPlayer = reinterpret_cast<Player*>(player->userData);
                Bumper* bumperBumper = reinterpret_cast<Bumper*>(bumper->userData);

                physx::PxVec3 launchVector; 
                launchVector = physx::PxVec3(bumperBumper->m_position.x - playerPlayer->m_position.x, 0.f, bumperBumper->m_position.z - playerPlayer->m_position.z);
                playerPlayer->AddEnvironmentalForce(launchVector * 0.2f);
            }
        }
    }
}

void CollisionHandler::onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count)
{

}
