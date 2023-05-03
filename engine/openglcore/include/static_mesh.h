#pragma once
#include "mesh.h"

namespace engine::openglcore
{
	class StaticMesh :public Mesh
	{
	public:
		StaticMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture>& textures);
		~StaticMesh();

		std::string getMeshType() const override;

		void setup(const std::function<void()>& layoutFunc = nullptr) override;

	private:
		std::vector<Vertex> vertices;

	};
}