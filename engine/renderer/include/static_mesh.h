#pragma once
#include "mesh.h"

namespace engine::renderer
{
    class StaticMesh :public Mesh
    {
    public:
        StaticMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        ~StaticMesh();

        std::string getMeshType() const override;
        void draw() override;

    private:
        void setup() override;
        std::vector<Vertex> vertices;
	};
}