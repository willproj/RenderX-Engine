#pragma once
#include "gui.h"

namespace engine::ui
{
	class ViewportGui :public Gui
	{
	public:
		ViewportGui();
		virtual ~ViewportGui();

		void render() override;

	};
}