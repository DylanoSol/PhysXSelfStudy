#include "Course.h"
#include "../physics/Physics.h"


Course::Course(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{

	m_courseData = LoadModelData("assets/testCourse2.gltf");

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
	
	physx::PxTriangleMeshDesc meshDescription; 
	meshDescription.points.count = m_vertices.size(); 
	meshDescription.points.stride = sizeof(physx::PxVec3); 
	meshDescription.points.data = &m_vertices[0]; 
	
	assert(meshDescription.isValid());

	physx::PxCookingParams waltuh = m_cooking->getParams(); 

	waltuh.midphaseDesc = physx::PxMeshMidPhase::eBVH33; 

	physx::PxU32 meshSize = 0; 
	physx::PxDefaultMemoryOutputStream outBuffer; 
	physx::PxTriangleMeshCookingResult::Enum result; 
	bool status = m_cooking->cookTriangleMesh(meshDescription, outBuffer, &result);
	if (!status) printf("doesn't work innit \n");

	physx::PxDefaultMemoryInputData stream(outBuffer.getData(), outBuffer.getSize()); 
	m_mesh = m_physics->createTriangleMesh(stream); 

	physx::PxShape* shape = m_physics->createShape(physx::PxTriangleMeshGeometry(m_mesh), *m_material);

	m_course = physx::PxCreateStatic(*m_physics, physx::PxTransform(position), *shape);
	m_physicsHandler->AddToWorld(m_course); 
}