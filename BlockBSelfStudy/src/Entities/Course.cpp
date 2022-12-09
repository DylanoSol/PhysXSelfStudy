#include "Course.h"
#include "../physics/Physics.h"


Course::Course(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics) : Entity(position, rotation, scale)
{

	m_courseData = LoadModelData("assets/testCourse.gltf");

	m_physicsHandler = physics;

	m_physics = m_physicsHandler->GetPhysics();

	m_cooking = m_physicsHandler->GetCooking(); 

	//Create material
	m_material = m_physics->createMaterial(0.2, 0.5, 0.8);


	//Generate triangle mesh

	//Get the vertices
	for (size_t i = 4; i < m_courseData->m_meshes.size(); i++)
	{
		for (size_t j = 0; j < m_courseData->m_meshes[i - 4]->m_positions.size(); j++)
		{
			m_vertices.push_back(m_courseData->m_meshes[i - 4]->m_positions[j]);
		}
	}

	//Get the indices 
	for (size_t i = 4; i < m_courseData->m_meshes.size(); i++)
	{
		for (size_t j = 0; j < m_courseData->m_meshes[i - 4]->m_indices.size(); j++)
		{
			m_indices.push_back(m_courseData->m_meshes[i - 4]->m_indices[j]);
		}
	}

	std::vector<glm::vec3> test; 
	
	for (size_t i = 0; i < m_indices.size(); i++)
	{
		test.push_back(m_vertices[m_indices[i]]);
	}

	physx::PxTriangleMeshDesc meshDescription; 
	meshDescription.points.count = test.size(); 
	meshDescription.points.stride = sizeof(physx::PxVec3); 
	meshDescription.points.data = &test[0]; 

	//For indexed meshes
	
//	meshDescription.triangles.count = m_indices.size(); 
//	meshDescription.triangles.stride = sizeof(physx::PxU32); 
//	meshDescription.triangles.data = &m_indices[0]; 
	
	assert(meshDescription.isValid());

	physx::PxCookingParams waltuh = m_cooking->getParams(); 

	waltuh.midphaseDesc = physx::PxMeshMidPhase::eBVH33; 

	physx::PxU32 meshSize = 0; 
	physx::PxDefaultMemoryOutputStream outBuffer; 
	physx::PxTriangleMeshCookingResult::Enum result; 
	bool status = m_cooking->cookTriangleMesh(meshDescription, outBuffer, &result);
	if (!status) printf("shit \n");

	physx::PxDefaultMemoryInputData stream(outBuffer.getData(), outBuffer.getSize()); 
	m_mesh = m_physics->createTriangleMesh(stream); 

	physx::PxShape* shape = m_physics->createShape(physx::PxTriangleMeshGeometry(m_mesh), *m_material);

	m_course = physx::PxCreateStatic(*m_physics, physx::PxTransform(5.f, 1.f, 0.f), *shape);
	m_physicsHandler->AddToWorld(m_course); 
}