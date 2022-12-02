#include "GLTFLoader.h"
#ifdef max
#undef max
#endif

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include <tiny_gltf.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <set>
#include <cmath>


void LoadMeshData(const tinygltf::Model* model,
	uint32_t nodeIdx, std::set<uint32_t>& nodeIndices, std::set<uint32_t>& meshIndices,
	std::vector<MeshInstance*>& meshInstances, std::vector<MeshData*>& meshDatas,
	glm::mat4 parentTransform, const std::string& path)
{
	if (nodeIndices.find(nodeIdx) != nodeIndices.end())
		return;
	nodeIndices.insert(nodeIdx);

	const auto& node = model->nodes[nodeIdx];

	glm::mat4 modelMatrix = parentTransform;
	glm::vec3 translation{};
	glm::quat rotation{};
	glm::vec3 scale(1, 1, 1);
	if (!node.matrix.empty())
	{
		float* elems = (float*)malloc(sizeof(float) * 16);
		for (size_t i = 0; i < 16; i++)
		{
			elems[i] = node.matrix[i];
		}
		modelMatrix = glm::make_mat4(elems) * modelMatrix;
		delete elems;

		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(modelMatrix, scale, rotation, translation, skew, perspective);
	}
	else
	{
		if (!node.rotation.empty())
		{
			rotation = glm::quat(static_cast<float>(node.rotation[3]), static_cast<float>(node.rotation[0]), static_cast<float>(node.rotation[1]), static_cast<float>(node.rotation[2]));
		}

		if (!node.scale.empty())
		{
			scale = glm::vec3(static_cast<float>(node.scale[0]), static_cast<float>(node.scale[1]), static_cast<float>(node.scale[2]));
		}

		if (!node.translation.empty())
		{
			translation = glm::vec3(static_cast<float>(node.translation[0]), static_cast<float>(node.translation[1]), static_cast<float>(node.translation[2]));
		}

		modelMatrix = glm::translate(glm::mat4(1.0f), translation) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale) * modelMatrix;

		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(modelMatrix, scale, rotation, translation, skew, perspective);
	}

	if (node.mesh != -1)
	{
		auto mesh = model->meshes[node.mesh];


		MeshInstance* meshInstance = new MeshInstance();
		meshInstance->m_position = translation;
		meshInstance->m_rotation = rotation;
		meshInstance->m_scale = scale;

		meshInstances.push_back(meshInstance);

		auto meshIter = meshIndices.find(node.mesh);
		if (meshIter == meshIndices.end())
		{
			meshIndices.insert(node.mesh);

			MeshData* meshData = new MeshData();
			meshDatas.push_back(meshData);
			meshInstance->m_meshDataIdx = meshDatas.size() - 1;
			meshData->node = node;

			auto primitive = mesh.primitives[0];

			if (primitive.material != -1) {
				auto& material = model->materials[primitive.material];
				int diffuseTextureIndex = material.pbrMetallicRoughness.baseColorTexture.index;

				if (diffuseTextureIndex != -1) {
					int source = model->textures[diffuseTextureIndex].source;
					meshInstance->m_diffuseTexture = model->images[source].uri;
				}
			}

			for (auto& attribute : primitive.attributes)
			{
				const auto& accessor = model->accessors[attribute.second];
				const auto& view = model->bufferViews[accessor.bufferView];
				const auto& buffer = model->buffers[view.buffer];

				// accessor.max / accessor.min

				if (attribute.first == "POSITION")
				{
					meshData->m_positions.reserve(accessor.count);
					meshData->m_positions.resize(accessor.count);
					memcpy(meshData->m_positions.data(), &buffer.data.at(view.byteOffset + accessor.byteOffset), accessor.count * sizeof(float) * 3);
				}
				else if (attribute.first == "NORMAL")
				{
					meshData->m_normals.reserve(accessor.count);
					meshData->m_normals.resize(accessor.count);
					memcpy(meshData->m_normals.data(), &buffer.data.at(view.byteOffset + accessor.byteOffset), accessor.count * sizeof(float) * 3);
				}
				else if (attribute.first == "TEXCOORD_0")
				{
					meshData->m_texCoords.reserve(accessor.count);
					meshData->m_texCoords.resize(accessor.count);
					memcpy(meshData->m_texCoords.data(), &buffer.data.at(view.byteOffset + accessor.byteOffset), accessor.count * sizeof(float) * 2);
				}
			}

			meshData->m_meshName = mesh.name;

			const auto& accessor = model->accessors[primitive.indices];
			const auto& view = model->bufferViews[accessor.bufferView];
			const auto& buffer = model->buffers[view.buffer];

			meshData->m_indices.reserve(accessor.count);
			meshData->m_indices.resize(accessor.count);

			if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
			{
				std::vector<uint16_t> smallIndices;
				smallIndices.reserve(accessor.count);
				smallIndices.resize(accessor.count);
				memcpy(smallIndices.data(), &buffer.data.at(view.byteOffset + accessor.byteOffset), accessor.count * sizeof(uint16_t));

				for (size_t i = 0; i < smallIndices.size(); i++)
				{
					meshData->m_indices[i] = static_cast<uint32_t>(smallIndices[i]);
				}
			}
			else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
			{
				memcpy(meshData->m_indices.data(), &buffer.data.at(view.byteOffset + accessor.byteOffset), accessor.count * sizeof(uint32_t));
			}
			else
			{
				
			}
		}
		else
		{
			meshInstance->m_meshDataIdx = *meshIter;
		}
	}

	for (auto c : node.children)
		LoadMeshData(model, c, nodeIndices, meshIndices, meshInstances, meshDatas, modelMatrix, path);
}

ModelData* LoadModelData(const std::string& path)
{
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	bool res = loader.LoadASCIIFromFile(&model, &err, &warn, path);

	std::set<uint32_t> nodeIndices;
	std::set<uint32_t> meshIndices;
	std::vector<MeshInstance*> instances;
	std::vector<MeshData*> meshes;
	for (const uint32_t node : model.scenes[0].nodes)
	{
		LoadMeshData(&model, node, nodeIndices, meshIndices, instances, meshes, glm::mat4(1.0f), path);
	}

	return new ModelData{ instances, meshes };
}