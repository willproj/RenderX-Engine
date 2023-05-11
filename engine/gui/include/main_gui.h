#pragma once
#include "gui.h"

namespace engine::ui
{
	class MainGui : public Gui
	{
	public:
		static std::shared_ptr<MainGui> getInstance();
		~MainGui();

		bool init();
		void renderAllGuis();
		
		static void uiFreeResource();

		static uint32_t getMainUiWidth();
		static uint32_t getMainUiHeight();

		static void setMainUiPos(int32_t xpos, int32_t ypos);

		static uint32_t getOffsetNavItemLeft();
		static uint32_t getOffsetNavItemRight();

		static uint32_t getNavbarHeight();
		static bool isFullScreen();

		void setRenderData(std::shared_ptr<scene::RenderData> renderData);

	private:

		MainGui();
		void uiSetup();
		void renderMainGui();
		void renderNavBar();
		void resetWindowSizePos(int32_t& set);

		static void uiStyle();
		
	private:

		std::string uiName;

		static bool isOpen;
		static bool fullscreen;

		static std::shared_ptr<MainGui> s_instance;

		static int32_t mainUiPosX;
		static int32_t mainUiPosY;

		static uint32_t mainUiWidth;
		static uint32_t mainUiHeight;

		static uint32_t offsetNavItemLeft;
		static uint32_t offsetNavItemRight;

		static uint32_t navbarHeight;

		std::vector<std::shared_ptr<Gui>> guiStack;

		uint32_t minimizeIcon;
		uint32_t maximizeIcon;
		uint32_t closeIcon;
		uint32_t restoreIcon;
		uint32_t logo;

		int32_t switchIcon;

		int32_t windowSizeX;
		int32_t windowSizeY;

		int32_t windowPosX;
		int32_t windowPosY;
	};
}