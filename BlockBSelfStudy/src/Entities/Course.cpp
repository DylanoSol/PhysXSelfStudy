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
	for (size_t i = 0; i < m_courseData->m_meshes.size(); i++)
	{
		for (size_t j = 0; j < m_courseData->m_meshes[i]->m_positions.size(); j++)
		{
			m_vertices.push_back(m_courseData->m_meshes[i]->m_positions[j]);
		}
	}

	physx::PxTriangleMeshDesc meshDescription; 
	meshDescription.points.count = m_vertices.size(); 
	meshDescription.points.stride = sizeof(physx::PxVec3); 
	meshDescription.points.data = &m_vertices[0]; 

	//Get the indices 
	for (size_t i = 0; i < m_courseData->m_meshes.size(); i++)
	{
		for (size_t j = 0; j < m_courseData->m_meshes[i]->m_indices.size(); j++)
		{
			m_indices.push_back(m_courseData->m_meshes[i]->m_indices[j]);
		}
	}

	meshDescription.triangles.count = m_indices.size(); 
	meshDescription.triangles.stride = sizeof(physx::PxU32); 
	meshDescription.points.data = &m_indices[0]; 
	

	
	
}