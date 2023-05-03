#include "include/static_mesh.h"

namespace engine::openglcore
{
	StaticMesh::StaticMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture>& textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
	}

	StaticMesh::~StaticMesh()
	{

	}

	std::string StaticMesh::getMeshType() const
	{
		return meshType;
	}

	void StaticMesh::setup(const std::function<void()>& layoutFunc)
	{
		layoutFunc();
	}



}