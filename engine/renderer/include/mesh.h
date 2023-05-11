#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "openglcore/include/vertexarray.h"
#include "openglcore/include/vertexbuffer.h"
#include "openglcore/include/indexbuffer.h"
#include "openglcore/include/texture.h"

namespace engine::renderer
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
        virtual void draw() = 0;
    protected:
        virtual void setup() = 0;
    protected:
        std::string meshType;
        std::vector<uint32_t> indices;

        openglcore::VertexArray vertexArray;
        openglcore::VertexBuffer vertexBuffer;
        openglcore::IndexBuffer indexBuffer;

         
    };
}