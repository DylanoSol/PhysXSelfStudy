#pragma once

#include <vector>
#include <cstdint>

#include <tiny_gltf.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/integer.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <PhysX/PxPhysicsAPI.h>

//Implementation derived from the OcEngine. 

	struct MeshInstance
	{
		uint32_t m_meshDataIdx;

		glm::vec3 m_position{};
		glm::quat m_rotation{};
		glm::vec3 m_scale{ 1, 1, 1 };

		std::string m_diffuseTexture;
	};

	struct MeshData
	{
		std::string m_meshName = "unnamed";
		std::string uuid = "";

		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_texCoords;

		std::vector<uint32_t> m_indices;
		tinygltf::Node node;
	};

	struct ModelData
	{
		~ModelData()
		{
			for (size_t i = 0; i < m_meshes.size(); i++)
			{
				delete m_meshes[i];
			}
		}

		std::vector<MeshInstance*> m_instances;
		std::vector<MeshData*> m_meshes;
	};
