#pragma once
#include "common.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <config.h>

namespace engine::ui
{
	class Gui
	{
	public:
		Gui();
		Gui(const Gui& other) = delete;
		Gui& operator=(const Gui& other) = delete;
		virtual ~Gui();
		
		virtual void render() = 0;
		virtual std::string getUiName() const;

		
	protected:
		std::string uiName;
	};
}

