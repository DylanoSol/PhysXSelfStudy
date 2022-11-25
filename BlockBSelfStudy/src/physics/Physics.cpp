#include "Physics.h"

Physics::Physics()
{
	InitializePhysics(); 
}

void Physics::InitializePhysics()
{

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

	//Create material
	m_material = m_physics->createMaterial(0.2, 0.5, 0.8); 

	physx::PxPlane* planeGeometry = new physx::PxPlane(0.f, 1.f, 0.f, 0.f);
	physx::PxRigidStatic* testPlane = physx::PxCreatePlane(*m_physics, *planeGeometry, *m_material);

	//Set rules of physics world. 
	m_dispatcher = physx::PxDefaultCpuDispatcherCreate(4);
	physx::PxSceneDesc sceneDescription(m_physics->getTolerancesScale());
	sceneDescription.gravity = physx::PxVec3(0.f, -9.81f, 0.f);
	sceneDescription.cpuDispatcher = m_dispatcher;
	sceneDescription.filterShader = physx::PxDefaultSimulationFilterShader;

	//Create scene
	m_physicsScene = m_physics->createScene(sceneDescription);

	//Add actors to test things
	AddToWorld(testPlane);

	//Set up PVD client
	physx::PxPvdSceneClient* pvdClient = m_physicsScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
}

void Physics::UpdatePhysics(float deltaTime)
{
	//replace with deltaTime
	m_physicsScene->simulate(1.f / 60.f);
	m_physicsScene->fetchResults(true);
}

void Physics::AddToWorld(physx::PxActor* actor)
{
	m_physicsScene->addActor(*actor); 
}

physx::PxPhysics* Physics::GetPhysics()
{
	return m_physics; 
}