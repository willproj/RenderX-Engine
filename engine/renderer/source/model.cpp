#include "include/model.h"
#include "include/static_mesh.h"

namespace engine::renderer
{
	Model::Model()
	{
		
	}
	
	Model::~Model()
	{

	}

    void Model::render()
    {
        for (uint64_t i = 0; i < meshes.size(); i++)
        {
            meshes[i]->draw();
        }
    }

    std::string Model::getPath() const
    {
        return path;
    }

	void Model::loadModel(const std::string& path)
	{
        if (!meshes.empty())
        {
            meshes.clear();
        }
        this->path = path;
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}
		// process ASSIMP's root node recursively
		processNode(scene->mRootNode, scene);
	}

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void Model::processNode(aiNode* node, const aiScene* scene)
    {
        // process each mesh located at the current node
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene. 
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }


    std::shared_ptr<Mesh> Model::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        // data to fill
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        // walk through each of the mesh's vertices
        for (uint64_t i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            // positions
            vertex.position = *(glm::vec3*) & mesh->mVertices[i];
            // normals
            if (mesh->HasNormals())
            {
                vertex.normal = *(glm::vec3*) & mesh->mNormals[i];
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vertex.texCoords = *(glm::vec2*)&mesh->mTextureCoords[0][i];
                // tangent
                vertex.tangent = *(glm::vec3*)&mesh->mTangents[i];
                // bitangent
                vertex.bitangent = *(glm::vec3*)&mesh->mBitangents[i];
            }
            else
                vertex.texCoords = glm::vec2(0.0f, 0.0f);

            vertices.emplace_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.emplace_back(face.mIndices[j]);
        }
       
        // return a mesh object created from the extracted mesh data
        return std::shared_ptr<StaticMesh>(new StaticMesh(vertices, indices));
    }
}