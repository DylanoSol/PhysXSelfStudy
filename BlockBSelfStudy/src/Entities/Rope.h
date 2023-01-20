#pragma once
#include "Entity.h"
#include <vector>

class Physics;
class Rope :
    public Entity
{
public:
    Rope(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale), Physics* physics);
    void Update(float deltaTime) override;
    void AddJoint(physx::PxRigidDynamic* bodyPart1, physx::PxRigidDynamic* bodyPart2);

private:
    Physics* m_physicsHandler = nullptr;

    physx::PxPhysics* m_physics = nullptr;

    physx::PxRigidStatic* m_origin = nullptr;

    physx::PxRigidDynamic* m_end = nullptr; 

    physx::PxRigidStatic* m_connectionPoint2 = nullptr; 

    std::vector<physx::PxRigidDynamic*> m_body; 

    std::vector<physx::PxSphericalJoint*> m_joints; 

    const int m_amountOfBodyParts = 100; 

    physx::PxMaterial* m_material = nullptr;

    physx::PxVec3* m_distance = nullptr; 
 
};

