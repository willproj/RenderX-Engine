#pragma once
#include "common.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <config.h>

#include "scene/render_scene.h"

namespace engine::ui
{
	class Gui
	{
	public:
		Gui();
		Gui(const Gui& other) = delete;
		Gui& operator=(const Gui& other) = delete;
		virtual ~Gui();
		
		virtual void render();
		std::string getUiName() const;
		bool* getIsOpenPtr();
		
		void set(std::shared_ptr<scene::RenderData> renderData);
	protected:
		std::string uiName;
		bool isOpen;

		static std::shared_ptr<scene::RenderData> s_renderData;
	};
}

