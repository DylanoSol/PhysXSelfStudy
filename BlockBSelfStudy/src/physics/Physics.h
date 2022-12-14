#pragma once
#include <PhysX/PxPhysicsAPI.h>

class CollisionHandler;
class Physics
{
public:
	Physics(); 
	void UpdatePhysics(float deltaTime); 

	//Add physics actor to the world.
	void AddToWorld(physx::PxActor* actor);

	//An entity needs this to be able to add a physics object. 
	physx::PxPhysics* GetPhysics(); 

	//The meshes use this
	physx::PxCooking* GetCooking(); 

	physx::PxPvd* m_pvd = NULL;
private:
	void InitializePhysics(); 

	physx::PxScene* m_physicsScene = NULL;
	physx::PxPhysics* m_physics = NULL;
	physx::PxFoundation* m_foundation = NULL;
	physx::PxDefaultCpuDispatcher* m_dispatcher = NULL;

	physx::PxCooking* m_cooking = nullptr; 

	//Foundation needs these
	physx::PxDefaultErrorCallback* m_errorCallback = NULL;
	physx::PxDefaultAllocator* m_allocator = NULL;

	physx::PxMaterial* m_material = nullptr; 

	physx::PxRigidDynamic* m_testSphere = nullptr; 

	CollisionHandler* m_collisionHandler = nullptr; 
};

