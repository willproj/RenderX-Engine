#include "include/main_gui.h"
#include "openglCore/include/window.h"

namespace engine::ui
{
	std::shared_ptr<MainGui> MainGui::s_instance;
	bool MainGui::showViewportGui = false;
	bool MainGui::showSceneGui = false;
	bool MainGui::p_open = true;
	bool MainGui::fullscreen = false;

	uint32_t MainGui::offsetNavItemLeft = 0;
	uint32_t MainGui::offsetNavItemRight = 0;

	uint32_t MainGui::mainUiWidth = WINDOW_DEFAULT_WIDTH;
	uint32_t MainGui::mainUiHeight = WINDOW_DEFAULT_HEIGHT;

	uint32_t MainGui::navbarHeight = 0;

	int32_t MainGui::mainUiPosX;
	int32_t MainGui::mainUiPosY;

	std::shared_ptr<MainGui> MainGui::getInstance()
	{
		if (s_instance == nullptr)
		{
			return std::shared_ptr<MainGui>(new MainGui());
		}
		return s_instance;
	}

	MainGui::MainGui()
		:uiName("RenderX")
	{
	}

	MainGui::~MainGui()
	{

	}

	bool MainGui::init()
	{
		uiSetup();
		return true;
	}


	uint32_t MainGui::getOffsetNavItemLeft()
	{
		return offsetNavItemLeft;
	}
	
	uint32_t MainGui::getOffsetNavItemRight()
	{
		return offsetNavItemRight;
	}

	uint32_t MainGui::getMainUiWidth()
	{
		return mainUiWidth;
	}

	uint32_t MainGui::getMainUiHeight()
	{
		return mainUiHeight;
	}

	uint32_t MainGui::getNavbarHeight()
	{
		return navbarHeight;
	}

	bool MainGui::isFullScreen()
	{
		return fullscreen;
	}

	void MainGui::setMainUiPos(int32_t xpos, int32_t ypos)
	{
		mainUiPosX = xpos;
		mainUiPosY = ypos;
	}


	void MainGui::renderMainGui()
	{
		static bool opt_fullscreen = false;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 10));
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		mainUiPosX = ImGui::GetWindowPos().x;
		mainUiPosY = ImGui::GetWindowPos().y;

		MainGui::mainUiWidth = ImGui::GetWindowSize().x;
		MainGui::mainUiHeight = ImGui::GetWindowSize().y;


		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}


		renderNavBar();
		


		ImGui::End();
		ImGui::PopStyleVar();


		ImGui::ShowDemoWindow();
	}

	void MainGui::renderNavBar()
	{

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
		ImGui::BeginMenuBar();
		
		offsetNavItemLeft = 10;
		offsetNavItemRight = 0;
		navbarHeight = ImGui::GetFrameHeight();

		if (ImGui::BeginMenu("Files"))
		{

			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::EndMenu();
		}
		offsetNavItemLeft += ImGui::GetItemRectSize().x;



		if (ImGui::BeginMenu("Options"))
		{
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::EndMenu();
		}
		offsetNavItemLeft += ImGui::GetItemRectSize().x;

		if (ImGui::BeginMenu("Settings"))
		{
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::MenuItem("EXIT				Alt+F4");
			ImGui::EndMenu();
		}
		offsetNavItemLeft += ImGui::GetItemRectSize().x;


		ImGui::EndMenuBar();
		ImGui::PopStyleVar();



	}

	void MainGui::renderAllGuis()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//render ui
		renderMainGui();
		//ImGui::ShowDemoWindow();


		// Rendering
		ImGui::Render();
		//int display_w, display_h;
		//glfwGetFramebufferSize(openglcore::Window::getInstance()->getGLFWwinPtr(), &display_w, &display_h);
		//glViewport(0, 0, display_w, display_h);
		//glClearColor(0.1f,0.1f,0.1f,0.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void MainGui::uiSetup()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
		ImGui::SetNextWindowPos(ImVec2(0,0));

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		std::string fontPath = ROOT_DIR; 
		fontPath+= "/assets/fonts/Segoe UI.ttf";
		io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 20);
		
		// Setup Dear ImGui style
		uiStyle();
		//ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(openglcore::Window::getInstance()->getGLFWwinPtr(), true);
		ImGui_ImplOpenGL3_Init("#version 430");
	}

	void MainGui::uiFreeResource()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void MainGui::uiStyle()
	{

		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
		style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
		style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		style.GrabRounding = style.FrameRounding = 2.3f;
	}


}