#include "renderxApp.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace engine::app
{
	std::string RenderXApp::s_appName = "RenderX";
	std::shared_ptr<RenderXApp> RenderXApp::app;

	std::shared_ptr<RenderXApp> RenderXApp::getInstance()
	{
		if (app == nullptr)
		{
			app = std::shared_ptr<RenderXApp>(new RenderXApp());
		}
		return app;
	}

	RenderXApp::RenderXApp()
	{
	}

	void RenderXApp::init()
	{
		openglWin = openglcore::Window::getInstance();
		mainGui = ui::MainGui::getInstance();
		openglWin->init();
		mainGui->init();

		openglWin->setEventCallbackFunc(std::bind(&input::InputManager::onEvent, &inputManager, std::placeholders::_1));
	}


	RenderXApp::~RenderXApp()
	{

	}

	void RenderXApp::tickRender()
	{
		openglWin->clear();

		mainGui->renderAllGuis();


		openglWin->winSwapBuffer();
	}

	void RenderXApp::tickLogic()
	{

	}

	void RenderXApp::run()
	{

		
		while (openglWin->isOpenglWinClose())
		{
			tickLogic();

			tickRender();
		}
	}



}