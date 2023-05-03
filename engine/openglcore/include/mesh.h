#pragma once
#include "thirdparty_header.h"

#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

#include "texture.h"


namespace engine::openglcore
{
	struct Vertex
	{
        // position
        glm::vec3 position;
        // normal
        glm::vec3 normal;
        // texCoords
        glm::vec2 texCoords;
        // tangent
        glm::vec3 tangent;
        // bitangent
        glm::vec3 bitangent;
	};


    class Mesh
    {
    public:

        Mesh();
        virtual ~Mesh();
        virtual std::string getMeshType() const = 0;

        virtual void setup(const std::function<void()>& layoutFunc = nullptr);
    protected:
        std::string meshType;
        std::vector<uint32_t> indices;
        std::vector<Texture> textures;

        VertexArray VAO;
        VertexBuffer VBO;
        IndexBuffer EBO;

    };
}