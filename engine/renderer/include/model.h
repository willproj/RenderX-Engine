#pragma once
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace engine::renderer
{
	class Model
	{
	public:
		Model();
		~Model();

		bool gammaCorrection;

		void loadModel(const std::string& path);
		std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
		void processNode(aiNode* node, const aiScene* scene);

		std::string getPath()const;

		void render();
	protected:
		std::vector<std::shared_ptr<Mesh>> meshes;
		std::string path;
	};
}