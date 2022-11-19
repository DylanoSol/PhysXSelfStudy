#pragma once
#include <PhysX/PxPhysicsAPI.h>

class Physics
{
public:
	Physics(); 
	void UpdatePhysics(float deltaTime); 

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
};

