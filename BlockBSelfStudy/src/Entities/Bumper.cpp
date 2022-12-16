#include "Bumper.h"
#include "../physics/Physics.h"

Bumper::Bumper(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{
	//Abstract this model loading code into something easier later: make sure you don't have to type this every time
	m_courseData = LoadModelData("assets/cylinder.gltf");

	m_physicsHandler = physics;

	m_physics = m_physicsHandler->GetPhysics();

	m_cooking = m_physicsHandler->GetCooking();

	//Create material
	m_material = m_physics->createMaterial(0.2, 0.5, 0.8);


	//Generate triangle mesh
	for (size_t i = 0; i < m_courseData->m_instances.size(); i++)
	{
		auto& instance = m_courseData->m_instances[i];
		auto& meshData = m_courseData->m_meshes[instance->m_meshDataIdx];

		for (size_t j = 0; j < meshData->m_indices.size(); j++)
		{
			m_vertices.push_back(meshData->m_positions[meshData->m_indices[j]]);
		}
	}

	//Send vertex data to PhysX
	physx::PxTriangleMeshDesc meshDescription;
	meshDescription.points.count = m_vertices.size();
	meshDescription.points.stride = sizeof(physx::PxVec3);
	meshDescription.points.data = &m_vertices[0];

	assert(meshDescription.isValid());

	//Cook mesh
	physx::PxCookingParams waltuh = m_cooking->getParams();

	waltuh.midphaseDesc = physx::PxMeshMidPhase::eBVH33;

	physx::PxU32 meshSize = 0;
	physx::PxDefaultMemoryOutputStream outBuffer;
	physx::PxTriangleMeshCookingResult::Enum result;
	bool status = m_cooking->cookTriangleMesh(meshDescription, outBuffer, &result);
	if (!status) printf("doesn't work innit \n");

	physx::PxDefaultMemoryInputData stream(outBuffer.getData(), outBuffer.getSize());
	m_mesh = m_physics->createTriangleMesh(stream);

	//Add to world
	physx::PxShape* shape = m_physics->createShape(physx::PxTriangleMeshGeometry(m_mesh, m_scale), *m_material);
	
	m_cylinder = physx::PxCreateStatic(*m_physics, physx::PxTransform(position), *shape);
	m_cylinder->setName("Bumper");
	
	m_physicsHandler->AddToWorld(m_cylinder);
}

void Bumper::Update(float deltaTime)
{

}