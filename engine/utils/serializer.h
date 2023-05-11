#pragma once
#include "common.h"
#include "scene/scene.h"

namespace engine::utils
{
    class Serializer
    {
    public:
        Serializer(scene::Scene* scene);

        void serialize(const std::string& path);
        bool deSerialize(const std::string& path);
        
        
    private:
        scene::Scene* scenePtr;
    };
}