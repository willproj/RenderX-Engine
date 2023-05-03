#include "include/dynamic_mesh.h"

namespace engine::openglcore
{
	DynamicMesh::DynamicMesh(const std::vector<DynamicVertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture>& textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
	}

	DynamicMesh::~DynamicMesh()
	{
	}
	std::string DynamicMesh::getMeshType() const
	{
		return std::string();
	}
	void DynamicMesh::setup(const std::function<void()>& layoutFunc)
	{
		layoutFunc();
	}
}