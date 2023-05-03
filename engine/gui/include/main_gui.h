#pragma once
#include "include/scene_gui.h"
#include "include/viewport_gui.h"

namespace engine::ui
{
	class MainGui
	{
	public:
		static std::shared_ptr<MainGui> getInstance();
		~MainGui();

		bool init();
		void renderAllGuis();
		
		static void uiFreeResource();

		static int32_t getMainUiPosX();
		static int32_t getMainUiPosY();

		static uint32_t getMainUiWidth();
		static uint32_t getMainUiHeight();

		static void setMainUiPos(int32_t xpos, int32_t ypos);

		static uint32_t getOffsetNavItemLeft();
		static uint32_t getOffsetNavItemRight();

		static uint32_t getNavbarHeight();

		static bool isFullScreen();


	private:

		MainGui();
		void uiSetup();
		void renderMainGui();

		static std::shared_ptr<MainGui> s_instance;
		static void uiStyle();

		static bool p_open;
		static bool fullscreen;

		
	private:
		void renderNavBar();

		std::string uiName;

		static int32_t mainUiPosX;
		static int32_t mainUiPosY;

		static uint32_t mainUiWidth;
		static uint32_t mainUiHeight;

		static uint32_t offsetNavItemLeft;
		static uint32_t offsetNavItemRight;

		static uint32_t navbarHeight;

		static bool showViewportGui;
		static bool showSceneGui;

		std::shared_ptr<SceneGui> sceneGui;
		std::shared_ptr<ViewportGui> viewport;

	};
}