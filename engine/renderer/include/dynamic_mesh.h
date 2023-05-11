#pragma once
#include "mesh.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine::renderer
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
		
		DynamicMesh(const std::vector<DynamicVertex>& vertices, const std::vector<uint32_t>& indices);
		~DynamicMesh();

		std::string getMeshType() const override;
		void draw() override; 
	private:
		void setup() override;
		std::vector<DynamicVertex> vertices;
	};
}