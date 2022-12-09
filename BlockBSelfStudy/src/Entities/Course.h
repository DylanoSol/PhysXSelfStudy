#pragma once
#include "Entity.h"
#include "../resources/GLTFLoader.h"

class Physics;
class Course :
    public Entity
{
public: 
    Course(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics);


private: 
    ModelData* m_courseData = nullptr; 

    Physics* m_physicsHandler = nullptr;

    physx::PxPhysics* m_physics = nullptr;

    physx::PxCooking* m_cooking = nullptr; 

    physx::PxMaterial* m_material = nullptr;

    physx::PxTriangleMesh* m_mesh = nullptr; 

    physx::PxRigidStatic* m_course = nullptr; 

    std::vector<glm::vec3> m_vertices;
    std::vector<int> m_indices; 
};

