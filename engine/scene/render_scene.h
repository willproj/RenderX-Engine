#pragma once
#include <common.h>
#include "openglcore/include/framebuffer.h"
#include "openglcore/include/gbuffer.h"
#include "renderer/include/editor_camera.h"
#include "renderer/include/skybox.h"
#include "scene.h"
#include "entity.h"
#include "openglcore/include/shader.h"
#include "renderer/include/IBL.h"

namespace engine::scene
{

	struct RenderData
	{

		Scene* scene;
		Entity entity1;
		renderer::EditorCamera* editorCameraOnUse;
		renderer::EditorCamera primaryEditorCamera;
		openglcore::Framebuffer framebuffer;
		Entity selectedEntity;
		bool isViewportOnFocus;
		renderer::IBL ibl;
	};

	struct ShaderPack
	{
		
	};


	class RenderScene
	{
	public:
		RenderScene();
		~RenderScene();

		void init();
		void renderScene();
		std::shared_ptr<RenderData> getRenderData() const;

	private:
		
		std::shared_ptr<RenderData> renderData;


		std::shared_ptr<openglcore::Shader> pbrShader;
		std::shared_ptr<openglcore::Shader> equirectangularToCubemapShader;
		std::shared_ptr<openglcore::Shader> irradianceShader;
		std::shared_ptr<openglcore::Shader> prefilterShader;
		std::shared_ptr<openglcore::Shader> brdfShader;
		std::shared_ptr<openglcore::Shader> backgroundShader;


		glm::vec3 lightPositions[4] = {
			glm::vec3(-10.0f,  10.0f, 10.0f),
			glm::vec3(10.0f,  10.0f, 10.0f),
			glm::vec3(-10.0f, -10.0f, 10.0f),
			glm::vec3(10.0f, -10.0f, 10.0f),
		};
		glm::vec3 lightColors[4] = {
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(500.0f, 300.0f, 300.0f),
			glm::vec3(500.0f, 300.0f, 300.0f),
			glm::vec3(500.0f, 300.0f, 300.0f)
		};

		int nrRows = 7;
		int nrColumns = 7;
		float spacing = 2.5;




	};
}