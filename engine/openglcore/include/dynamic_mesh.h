#pragma once
#include "mesh.h"

namespace engine::openglcore
{
	struct DynamicVertex :public Vertex
	{
		//bone indexes which will influence this vertex
		int boneIDs[MAX_BONE_INFLUENCE];
		//weights from each bone
		float weights[MAX_BONE_INFLUENCE];
	};


	class DynamicMesh :public Mesh
	{
	public:
		DynamicMesh(const std::vector<DynamicVertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Texture>& textures);
		~DynamicMesh();

		std::string getMeshType() const override;

		void setup(const std::function<void()>& layoutFunc = nullptr) override;
	private:
		std::vector<DynamicVertex> vertices;
	};
}