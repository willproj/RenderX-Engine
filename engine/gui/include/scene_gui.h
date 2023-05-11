#pragma once
#include "gui.h"
#include "scene/entity.h"

namespace engine::ui
{
	class SceneGui :public Gui
	{
	public:
		SceneGui();
		~SceneGui();

		SceneGui(const SceneGui& other) = delete;
		SceneGui& operator=(const SceneGui& other) = delete;

		void render() override;
	private:
		void renderEntityInfo(scene::Entity& entity, static int& selected);

		uint32_t objIcon;

		bool isItemHovered;
	};
}