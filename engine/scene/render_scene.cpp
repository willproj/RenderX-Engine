#include "render_scene.h"
#include "openglcore/include/window.h"
#include "component.h"

#include "openglcore/include/vertexarray.h"

#include "utils/serializer.h"
#include "utils/filesystem.h"

namespace engine::scene
{
	RenderScene::RenderScene()
	{
		init();
	}
	
	RenderScene::~RenderScene()
	{

	}

	void RenderScene::init()
	{

		uint32_t width = openglcore::Window::getInstance()->getWidth();
		uint32_t height = openglcore::Window::getInstance()->getHeight();

		renderData = std::shared_ptr<RenderData>(new RenderData());
		renderData->framebuffer.create(width, height);
        renderData->primaryEditorCamera.setCameraAttributes(45.0f, (float)width / (float)height, 0.1f, 10000.0f);
        renderData->editorCameraOnUse = &renderData->primaryEditorCamera;

        renderData->scene = new Scene();

        pbrShader = std::shared_ptr<openglcore::Shader>(new openglcore::Shader(
            utils::FileSystem::getRootPath() + "/assets/shader/IBL/pbr.vs", utils::FileSystem::getRootPath() + "/assets/shader/IBL/pbr.fs"));
        equirectangularToCubemapShader = std::shared_ptr<openglcore::Shader>(new openglcore::Shader(
            utils::FileSystem::getRootPath() + "/assets/shader/IBL/cubemap.vs", utils::FileSystem::getRootPath() + "/assets/shader/IBL/equirectangular_to_cubemap.fs"));
        irradianceShader = std::shared_ptr<openglcore::Shader>(new openglcore::Shader(
            utils::FileSystem::getRootPath() + "/assets/shader/IBL/cubemap.vs", utils::FileSystem::getRootPath() + "/assets/shader/IBL/irradiance_convolution.fs"));
        prefilterShader = std::shared_ptr<openglcore::Shader>(new openglcore::Shader(
            utils::FileSystem::getRootPath() + "/assets/shader/IBL/cubemap.vs", utils::FileSystem::getRootPath() + "/assets/shader/IBL/prefilter.fs"));
        brdfShader = std::shared_ptr<openglcore::Shader>(new openglcore::Shader(
            utils::FileSystem::getRootPath() + "/assets/shader/IBL/brdf.vs", utils::FileSystem::getRootPath() + "/assets/shader/IBL/brdf.fs"));
        backgroundShader = std::shared_ptr<openglcore::Shader>(new openglcore::Shader(
            utils::FileSystem::getRootPath() + "/assets/shader/IBL/background.vs", utils::FileSystem::getRootPath() + "/assets/shader/IBL/background.fs"));


        pbrShader->UseShaderProgram();
        pbrShader->SetInt("irradianceMap", 0);
        pbrShader->SetInt("prefilterMap", 1);
        pbrShader->SetInt("brdfLUT", 2);
        pbrShader->SetVec3("albedo", 0.5f, 0.0f, 0.0f);
        pbrShader->SetFloat("ao", 1.0f);

        backgroundShader->UseShaderProgram();
        backgroundShader->SetInt("environmentMap", 0);

        renderData->ibl.create(equirectangularToCubemapShader, irradianceShader, prefilterShader, brdfShader);
        int scrWidth, scrHeight;
        glfwGetFramebufferSize(openglcore::Window::getInstance()->getGLFWwinPtr(), &scrWidth, &scrHeight);
        glViewport(0, 0, scrWidth, scrHeight);


	}

	void RenderScene::renderScene()
	{
        renderData->framebuffer.bindFramebuffer();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto& cam = renderData->primaryEditorCamera;

        renderData->framebuffer.clearAttachmentForPicker();

        pbrShader->UseShaderProgram();
        pbrShader->SetVec3("camPos", cam.getPosition());
        pbrShader->SetMat4("projection", cam.getProjection());
        pbrShader->SetMat4("view", cam.getViewMatrix());
        
        glm::mat4 model = glm::mat4(1.0f);
        
        
        renderData->scene->getRegisterRef().each([&](auto entityID)
        {
                Entity entity = { entityID, renderData->scene };
                
                pbrShader->SetInt("entity", (int)entityID);

                if (entity.hasComponent<TransformComponent>())
                {
                    auto& transform = entity.getComponent<TransformComponent>();
                    pbrShader->SetMat4("model", transform.getTransform());
                    pbrShader->SetMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(transform.getTransform()))));
                }

                if (entity.hasComponent<MaterialComponent>())
                {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_CUBE_MAP, renderData->ibl.irradianceMap);
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_CUBE_MAP, renderData->ibl.prefilterMap);
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, renderData->ibl.brdfLUTTexture);

                    auto& materialComp = entity.getComponent<MaterialComponent>();
                    pbrShader->SetFloat("metallic", materialComp.metallic);
                    pbrShader->SetFloat("roughness", materialComp.roughness);
                    pbrShader->SetVec3("albedo", materialComp.albedo);
                }
                else
                {
                    pbrShader->SetFloat("metallic", 0.5f);
                    pbrShader->SetFloat("roughness", 0.5f);
                    pbrShader->SetVec3("albedo", glm::vec3(1.0f));
                }
                

                if (entity.hasComponent<ModelComponent>())
                {
                    auto& modelComp = entity.getComponent<ModelComponent>();
                    modelComp.model.render();
                }

               

        });


        //for (unsigned int i = 0; i < 4; ++i)
        //{
        //    glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        //    newPos = lightPositions[i];
        //    shader->SetVec3("lightPositions[" + std::to_string(i) + "]", newPos);
        //    shader->SetVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
        //
        //    model = glm::mat4(1.0f);
        //    model = glm::translate(model, newPos);
        //    model = glm::scale(model, glm::vec3(0.5f));
        //    shader->SetMat4("model", model);
        //    shader->SetMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
        //}


        // render skybox (render as last to prevent overdraw)
        backgroundShader->UseShaderProgram();
        backgroundShader->SetMat4("projection", cam.getProjection());
        backgroundShader->SetMat4("view", cam.getViewMatrix());
        glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_CUBE_MAP, renderData->ibl.envCubemap);
        glBindTexture(GL_TEXTURE_CUBE_MAP, renderData->ibl.irradianceMap); // display irradiance map
        //glBindTexture(GL_TEXTURE_CUBE_MAP, renderData->ibl.prefilterMap); // display prefilter map
        renderData->ibl.renderCube();

        //brdfShader->UseShaderProgram();
        //renderData->ibl.renderQuad();


		renderData->framebuffer.unbindFramebuffer();
        cam.update();

	}

	std::shared_ptr<RenderData> RenderScene::getRenderData()const
	{
		return renderData;
	}

}