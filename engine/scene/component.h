#pragma once

#include "common.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "renderer/include/model.h"
#include "renderer/include/light.h"
#include "renderer/include/editor_camera.h"

namespace engine::scene
{

	struct UUIDComponent
	{
		uint64_t uuid;
		
		UUIDComponent() = default;
		UUIDComponent(const UUIDComponent&) = default;
		UUIDComponent& operator=(const UUIDComponent&) = default;
	};

	struct LabelComponent
	{
		std::string label;

		LabelComponent() = default;
		LabelComponent(const LabelComponent&) = default;
		LabelComponent& operator=(const LabelComponent&) = default;

		LabelComponent(const std::string& label) :label(label) {}
	};


	struct TransformComponent
	{
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
		glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent& operator=(const TransformComponent&) = default;

		glm::mat4 getTransform() const
		{

			glm::mat4 rotationMat = glm::toMat4(glm::quat(rotation));
			
			return glm::translate(glm::mat4(1.0f), translation)
				* rotationMat
				* glm::scale(glm::mat4(1.0f), scale);
		}
	};

	struct CameraComponent
	{
		renderer::EditorCamera editorCamera;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent& operator=(const CameraComponent&) = default;

	};


	struct LightComponent
	{
		renderer::Light light;

		LightComponent() = default;
		LightComponent(const LightComponent&) = default;
		LightComponent& operator=(const LightComponent&) = default;
	};

	struct MaterialComponent
	{
		glm::vec3 albedo = { 1.0f,1.0f,1.0f };
		float metallic = 0.5f;
		float roughness = 0.5f;
		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;
		MaterialComponent& operator=(const MaterialComponent&) = default;
	};

	struct ColorComponent
	{
		glm::vec3 color;

		ColorComponent() = default;
		ColorComponent(const ColorComponent&) = default;
		ColorComponent& operator=(const ColorComponent&) = default;
	};


	struct ModelComponent
	{
		renderer::Model model;

		ModelComponent() = default;
		ModelComponent(const ModelComponent&) = default;
		ModelComponent& operator=(const ModelComponent&) = default;

	};

}