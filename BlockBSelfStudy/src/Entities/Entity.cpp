#include "Entity.h"

Entity::Entity(physx::PxVec3(position), physx::PxQuat(rotation), physx::PxVec3(scale)) : m_position(position), m_rotation(rotation), m_scale(scale)
{

};
