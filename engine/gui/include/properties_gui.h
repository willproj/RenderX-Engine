#pragma once
#include "gui.h"
#include "scene/component.h"

namespace engine::ui
{
	class PropertiesGui :public Gui
	{
	public:
		PropertiesGui();
		~PropertiesGui();

		PropertiesGui(const PropertiesGui& other) = delete;
		PropertiesGui& operator=(const PropertiesGui& other) = delete;

		void render() override;
	private:
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
		
		void renderUUIDComponentProperty(scene::UUIDComponent& UUIDComponent);
		void renderLabelComponentProperty(scene::LabelComponent& LabelComponent);
		void renderTransformComponentProperty(scene::TransformComponent& transformComponent);
		void renderModelComponentProperty(scene::ModelComponent& modelComponent);
		void renderMaterialComponentProperty(scene::MaterialComponent& materialComponent);
		void renderCameraComponentProperty(scene::CameraComponent& cameraComponent);
		void renderLightComponentProperty(scene::LightComponent& lightComponent);
		void renderColorComponentProperty(scene::ColorComponent& colorComponent);
		
		void addComponentPopupWindow();
	};
}