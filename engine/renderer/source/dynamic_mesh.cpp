#include "include/dynamic_mesh.h"

namespace engine::renderer
{
	DynamicMesh::DynamicMesh(const std::vector<DynamicVertex>& vertices, const std::vector<uint32_t>& indices)
	{
		this->vertices = vertices;
		this->indices = indices;
	}

	DynamicMesh::~DynamicMesh()
	{
	}

	std::string DynamicMesh::getMeshType() const
	{
		return std::string();
	}

	void DynamicMesh::setup()
	{
	}

	void DynamicMesh::draw()
	{

	}



}