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
	physx::PxTransform parentTransform, const std::string& path)
{
	
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
		//LoadMeshData(&model, node, nodeIndices, meshIndices, instances, meshes, glm::mat4(1.0f), path);
	}

	return new ModelData{ instances, meshes };
}