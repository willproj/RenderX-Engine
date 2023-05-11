#include "include/static_mesh.h"

namespace engine::renderer
{
	StaticMesh::StaticMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
	{
		this->vertices = vertices;
		this->indices = indices;

		setup();
	}

	StaticMesh::~StaticMesh()
	{

	}

	std::string StaticMesh::getMeshType() const
	{
		return meshType;
	}

	void StaticMesh::draw()
	{
		vertexArray.bind();
		indexBuffer.draw(static_cast<uint32_t>(indices.size()));
		vertexArray.unbind();
	}

	void StaticMesh::setup()
	{
		vertexArray.bind();
		
		vertexBuffer.bind();
		vertexBuffer.addBufferData(vertices.size() * sizeof(Vertex), &vertices[0]);

		indexBuffer.bind();
		indexBuffer.addBufferData(indices.size() * sizeof(uint32_t), &indices[0]);

		vertexBuffer.addBufferLayout<float, 0, 3>(sizeof(Vertex), 0);
		vertexBuffer.addBufferLayout<float, 1, 3>(sizeof(Vertex), offsetof(Vertex, Vertex::normal));
		vertexBuffer.addBufferLayout<float, 2, 2>(sizeof(Vertex), offsetof(Vertex, Vertex::texCoords));
		vertexBuffer.addBufferLayout<float, 3, 3>(sizeof(Vertex), offsetof(Vertex, Vertex::tangent));
		vertexBuffer.addBufferLayout<float, 4, 3>(sizeof(Vertex), offsetof(Vertex, Vertex::bitangent));

	}



}