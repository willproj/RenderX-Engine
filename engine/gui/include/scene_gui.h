#pragma once
#include "gui.h"

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


	};
}