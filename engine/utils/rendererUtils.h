#pragma once
#include "common.h"

namespace engine::utils
{
    class RendererUtils
    {
    public:
        static void renderCube();
        static void renderQuad();
    private:
        static uint32_t quadVAO;
        static uint32_t quadVBO;

        static uint32_t cubeVAO;
        static uint32_t cubeVBO;
    };
}