#pragma once
#include <PhysX/PxPhysicsAPI.h>

class Physics
{
public:
	Physics(); 
	void UpdatePhysics(float deltaTime); 
	void AddToWorld(physx::PxActor* actor);

private:
	void InitializePhysics(); 

	physx::PxScene* m_physicsScene = NULL;
	physx::PxPhysics* m_physics = NULL;
	physx::PxFoundation* m_foundation = NULL;
	physx::PxPvd* m_pvd = NULL;
	physx::PxDefaultCpuDispatcher* m_dispatcher = NULL;

	//Foundation needs these
	physx::PxDefaultErrorCallback* m_errorCallback = NULL;
	physx::PxDefaultAllocator* m_allocator = NULL;

	physx::PxMaterial* m_material = nullptr; 

	physx::PxRigidDynamic* m_testSphere = nullptr; 


	float m_testCountdown = 10000.f; 
};

