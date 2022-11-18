#include <string>
#include <PhysX/PxPhysicsAPI.h>


physx::PxScene* m_physicsScene = NULL;
physx::PxPhysics* m_physics = NULL;
physx::PxFoundation* m_foundation = NULL;
physx::PxPvd* m_pvd = NULL;
physx::PxDefaultCpuDispatcher* m_dispatcher = NULL;

//Foundation needs these
physx::PxDefaultErrorCallback* m_errorCallback = NULL;
physx::PxDefaultAllocator* m_allocator = NULL;

int main(int argc, char* args[])
{
	printf("Hello World");

		m_allocator = new physx::PxDefaultAllocator();
		m_errorCallback = new physx::PxDefaultErrorCallback();

		//Foundation provides the basis for the physics.
		m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, *m_allocator, *m_errorCallback);

		//PhysX visual debugger. 
		m_pvd = PxCreatePvd(*m_foundation);
		physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
		m_pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

		//Create definition of physics world. 
		m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, physx::PxTolerancesScale(), true, m_pvd);

		//Set rules of physics world. 
		m_dispatcher = physx::PxDefaultCpuDispatcherCreate(4);
		physx::PxSceneDesc sceneDescription(m_physics->getTolerancesScale());
		sceneDescription.gravity = physx::PxVec3(0.f, -9.81f, 0.f);
		sceneDescription.cpuDispatcher = m_dispatcher;
		sceneDescription.filterShader = physx::PxDefaultSimulationFilterShader;

		//Create scene
		m_physicsScene = m_physics->createScene(sceneDescription);

		//Set up PVD client
		physx::PxPvdSceneClient* pvdClient = m_physicsScene->getScenePvdClient();
		if (pvdClient)
		{
			pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
			pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
			pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
		}

	while (true)
	{
		//replace with deltaTime
		m_physicsScene->simulate(1.f / 60.f);
		m_physicsScene->fetchResults(true);
	}

	return 0; 
}