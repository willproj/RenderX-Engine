#pragma once
#include "gui.h"
#include <glm/glm.hpp>

namespace engine::ui
{
	class ViewportGui :public Gui
	{
	public:
		ViewportGui();
		virtual ~ViewportGui();

		void render() override;

		void onEvent(const std::function<void()>& func);
		void renderImGuizmo();
	private:
		glm::vec2 viewportSize;
		glm::vec2 viewportBounds[2]; 
		int32_t guizmoType = -1;
	};
}