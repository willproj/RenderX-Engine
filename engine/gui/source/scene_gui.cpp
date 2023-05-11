#include "include/scene_gui.h"
#include "scene/render_scene.h"
#include "scene/component.h"
#include "utils/filesystem.h"
#include "input/keyboard.h"

namespace engine::ui
{
	SceneGui::SceneGui()
	{
		uiName = "Scene";
		isOpen = true;
		isItemHovered = false;
	}

	SceneGui::~SceneGui()
	{

	}

	void SceneGui::render()
	{
		if (isOpen)
		{
			ImGui::Begin(uiName.c_str(), &isOpen);
			static int selected = -1;
			s_renderData->scene->getRegisterRef().each([&](auto entityID) {
				scene::Entity entity{ entityID, s_renderData->scene };
				renderEntityInfo(entity, selected);
			});

			if (ImGui::IsAnyMouseDown() && ImGui::IsWindowHovered())
			{
				s_renderData->selectedEntity = {};
				selected = -1;
			}
			
			if (!isItemHovered)
			{
				if (ImGui::BeginPopupContextWindow("pop up", ImGuiPopupFlags_MouseButtonRight))
				{
					if (ImGui::MenuItem("Create Empty Entity"))
					{
						s_renderData->scene->createEntity("Entity");
					}
					ImGui::EndPopup();
				}
			}

			isItemHovered = false;
			ImGui::End();
		}
	}

	void SceneGui::renderEntityInfo(scene::Entity& entity, static int& selected)
	{
		auto label = entity.getComponent<scene::LabelComponent>().label;

		auto tex = openglcore::TextureUtils::loadTexture(utils::FileSystem::getRootPath() + "/assets/icon/objFile.png");
		ImGui::Image((ImTextureID)tex, ImVec2(20, 20), ImVec2(1,1), ImVec2(0,0)); ImGui::SameLine(); 
		
		label += "##"+ std::to_string(entity());
		if (ImGui::Selectable(label.c_str(), selected == entity()))
		{
			selected = entity();
			s_renderData->selectedEntity = entity;
		}

		if (ImGui::BeginPopupContextItem())
		{
			selected = entity();
			if (ImGui::MenuItem("Delete Entity"))
			{
				s_renderData->scene->removeEntity(entity);
			}
			ImGui::EndPopup();
		}
		if (ImGui::IsItemHovered())
		{
			isItemHovered = true;
		}

	}

}