#pragma once
#include "common.h"
#include "openglcore/include/shader.h"

namespace engine::renderer
{
	class IBL
	{
	public:
		IBL();
		~IBL();

		void create(std::shared_ptr<openglcore::Shader> equirectangularToCubemapShader,
			std::shared_ptr<openglcore::Shader> irradianceShader,
			std::shared_ptr<openglcore::Shader> prefilterShader,
			std::shared_ptr<openglcore::Shader> brdfShader);

		unsigned int hdrTexture;
		unsigned int envCubemap;
		unsigned int irradianceMap;
		unsigned int prefilterMap;
		unsigned int brdfLUTTexture;

		void renderCube();
		void renderQuad();
	private:
		unsigned int quadVAO = 0;
		unsigned int quadVBO;

		unsigned int cubeVAO = 0;
		unsigned int cubeVBO = 0;
	};
}