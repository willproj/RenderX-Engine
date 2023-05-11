#pragma once
#include "gui/include/main_gui.h"
#include "openglCore/include/window.h"
#include "input/input_manager.h"
#include "scene/render_scene.h"


namespace engine::app
{
	class RenderXApp
	{
	public:
		~RenderXApp();
		static std::shared_ptr<RenderXApp> getInstance();
		void init();

		void run();

	private:
		RenderXApp();

		void tickRender();
		void tickLogic();
	private:

		static std::string s_appName;
		static std::shared_ptr<RenderXApp> app;


		std::shared_ptr<openglcore::Window> openglWin;
		std::shared_ptr<ui::MainGui> mainGui;
		std::shared_ptr<scene::RenderScene> renderScene;

		input::InputManager inputManager;

	};
}