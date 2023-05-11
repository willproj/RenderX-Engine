#include "include/properties_gui.h"
#include <imgui_internal.h>
#include <utils/filesystem.h>

namespace engine::ui
{
	PropertiesGui::PropertiesGui()
	{
		isOpen = true;
		uiName = "Properties";

	}

	PropertiesGui::~PropertiesGui()
	{

	}

	void PropertiesGui::render()
	{
		if (isOpen)
		{
			ImGui::Begin(uiName.c_str(), &isOpen);
			auto& selectedEntity = s_renderData->selectedEntity;

			if (selectedEntity.isEmptyEntity())
			{
				ImGui::End();
				return;
			}

			if (selectedEntity.hasComponent<scene::UUIDComponent>())
			{
				auto& uuidComp = selectedEntity.getComponent<scene::UUIDComponent>();
				renderUUIDComponentProperty(uuidComp);
			}

			if (selectedEntity.hasComponent<scene::LabelComponent>())
			{
				auto& tagComponent = selectedEntity.getComponent<scene::LabelComponent>();
				renderLabelComponentProperty(tagComponent);
				addComponentPopupWindow();
				ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
			}

			if (selectedEntity.hasComponent<scene::TransformComponent>())
			{
				auto& transformComponent = selectedEntity.getComponent<scene::TransformComponent>();
				renderTransformComponentProperty(transformComponent);
			}

			if (selectedEntity.hasComponent<scene::ModelComponent>())
			{
				auto& modelComponent = selectedEntity.getComponent<scene::ModelComponent>();
				renderModelComponentProperty(modelComponent);

			}

			if (selectedEntity.hasComponent<scene::MaterialComponent>())
			{
				auto& materialComp = selectedEntity.getComponent<scene::MaterialComponent>();
				renderMaterialComponentProperty(materialComp);

			}
			
			if (selectedEntity.hasComponent<scene::CameraComponent>())
			{
				auto& cameraComponent = selectedEntity.getComponent<scene::CameraComponent>();
				renderCameraComponentProperty(cameraComponent);
			}

			
			if (selectedEntity.hasComponent<scene::ColorComponent>())
			{
				auto& colorComponent = selectedEntity.getComponent<scene::ColorComponent>();
				renderColorComponentProperty(colorComponent);

			}

			if (selectedEntity.hasComponent<scene::LightComponent>())
			{
				auto& lightComponent= selectedEntity.getComponent<scene::LightComponent>();
				renderLightComponentProperty(lightComponent);

			}


			ImGui::End();
		}

	}

	void PropertiesGui::addComponentPopupWindow()
	{
		ImGui::SameLine();
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("Components Popup");
		ImGui::SameLine();
		if (ImGui::BeginPopup("Components Popup"))
		{
			if (ImGui::MenuItem("Transform Component"))
			{
				s_renderData->selectedEntity.addComponent<scene::TransformComponent>();
			}

			if (ImGui::MenuItem("Model Component"))
			{
				s_renderData->selectedEntity.addComponent<scene::ModelComponent>();
			}

			if (ImGui::MenuItem("Material Component"))
			{
				s_renderData->selectedEntity.addComponent<scene::MaterialComponent>();
			}




			ImGui::EndPopup();
		}
	}

	void PropertiesGui::renderUUIDComponentProperty(scene::UUIDComponent& UUIDComponent)
	{

		ImGui::Text("Entity UUID: ");
		ImGui::SameLine();
		ImGui::Text(std::to_string(UUIDComponent.uuid).c_str());
	}


	void PropertiesGui::renderLabelComponentProperty(scene::LabelComponent& tagComponent)
	{
		
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tagComponent.label.c_str());
		ImGui::Text("Label"); ImGui::SameLine();
		ImGui::SetNextItemWidth(160);
		if(ImGui::InputText("##Label", buffer, sizeof(buffer)))
		{
			std::string newLabel = std::string(buffer);
			tagComponent.label = newLabel == "" ? " " : newLabel;
		}

	}


	static void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });



		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}


	void PropertiesGui::renderTransformComponentProperty(scene::TransformComponent& transformComponent)
	{
		if (ImGui::CollapsingHeader("Transform", flags))
		{
			ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
			drawVec3Control("Translation", transformComponent.translation);
			ImGui::Spacing();
			glm::vec3 rotation = glm::degrees(transformComponent.rotation);
			drawVec3Control("Rotation", rotation);
			ImGui::Spacing();
			transformComponent.rotation = glm::radians(rotation);
			drawVec3Control("Scale", transformComponent.scale, 1.0f);
			ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

		}
	}

	void PropertiesGui::renderModelComponentProperty(scene::ModelComponent& modelComponent)
	{
		if (ImGui::CollapsingHeader("Model", flags))
		{
			ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
			if (ImGui::Button("Load Mesh"))
			{
				std::string filePath = utils::FileSystem::openFile("fbx (*.fbx)\0*.fbx\0obj (*.obj)\0*.obj\0");
				auto& modelComp = s_renderData->selectedEntity.getComponent<scene::ModelComponent>();
				if (!filePath.empty())
				{
					modelComp.model.loadModel(filePath);
				}
			}
			ImGui::SameLine();
			std::string path = s_renderData->selectedEntity.getComponent<scene::ModelComponent>().model.getPath();
			ImGui::Text(utils::FileSystem::getFilenameInFilepath(path).c_str());
			ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
		}
	}


	void PropertiesGui::renderMaterialComponentProperty(scene::MaterialComponent& materialComponent)
	{
		if (ImGui::CollapsingHeader("Material", flags))
		{
			ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

			ImGui::PushID(s_renderData->selectedEntity.getComponent<scene::LabelComponent>().label.c_str());
			auto& materialComp = s_renderData->selectedEntity.getComponent<scene::MaterialComponent>();
			ImGui::ColorEdit3("MyColor##1", (float*)&materialComp.albedo);
			ImGui::PopID();
			
			ImGui::PushID(s_renderData->selectedEntity.getComponent<scene::LabelComponent>().label.c_str());
			ImGui::SliderFloat("Roughness", (float*)&materialComp.roughness, 0.0f, 1.0f);
			ImGui::PopID();
			
			ImGui::PushID(s_renderData->selectedEntity.getComponent<scene::LabelComponent>().label.c_str());
			ImGui::SliderFloat("Metallic", (float*)&materialComp.metallic, 0.0f, 1.0f);
			ImGui::PopID();


			ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
		}
	}


	void PropertiesGui::renderCameraComponentProperty(scene::CameraComponent& cameraComponent)
	{
		if (ImGui::CollapsingHeader("Camera", flags))
		{

			ImGui::Spacing();
		}
	}
	
	
	void PropertiesGui::renderLightComponentProperty(scene::LightComponent& lightComponent)
	{
		if (ImGui::CollapsingHeader("Light", flags))
		{

			ImGui::Spacing();
		}
	}

	void PropertiesGui::renderColorComponentProperty(scene::ColorComponent& colorComponent)
	{
		if (ImGui::CollapsingHeader("Color", flags))
		{

			ImGui::Spacing();
		}
	}


}
