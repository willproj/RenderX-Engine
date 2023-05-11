#include "include/window.h"
#include "gui/include/main_gui.h"
#include "input/mouse.h"

#include "stb/stb_image.h"
#include "utils/filesystem.h"

#include <chrono>

namespace engine::openglcore
{

	std::shared_ptr<Window> Window::s_Instance;

	std::shared_ptr<Window> Window::getInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = std::shared_ptr<Window>(new Window());
		}
		return s_Instance;
	}

	Window::Window()
	{
		winSpeci.width = WINDOW_DEFAULT_WIDTH;
		winSpeci.height = WINDOW_DEFAULT_HEIGHT;
	}

	Window::~Window()
	{

	}

	void Window::setWindowPos(uint32_t xpos, uint32_t ypos)
	{
		//winSpeci.mouse_xpos = xpos;
		//winSpeci.mouse_ypos = ypos;
	}

	void Window::windowPosCallback(GLFWwindow* window, uint32_t xpos, uint32_t ypos)
	{
		glfwSetWindowPos(window, xpos, ypos);
	}

	void Window::setEventCallbackFunc(const std::function<void(event::Event&)>& eventCallbackFunc)
	{
		winSpeci.eventCallbackFunc = eventCallbackFunc;
	}

	bool Window::init()
	{
		// glfw: initialize and configure
		// ------------------------------
		if (!glfwInit())
		{
			return false;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

		glfwWindowHint(GLFW_AUTO_ICONIFY, GL_TRUE);

		//glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);



		winSpeci.openglWinPtr= glfwCreateWindow(winSpeci.width, winSpeci.height, winSpeci.title.c_str(), nullptr, nullptr);
		if (winSpeci.openglWinPtr == nullptr)
		{
			
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwSetWindowUserPointer(winSpeci.openglWinPtr, &winSpeci);
		
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		winSpeci.windowXPos = (mode->width - winSpeci.width) / 2;
		winSpeci.windowYPos = (mode->height - winSpeci.height) / 2;
		glfwSetWindowPos(winSpeci.openglWinPtr, winSpeci.windowXPos, winSpeci.windowYPos);
		ui::MainGui::setMainUiPos(winSpeci.windowXPos, winSpeci.windowYPos);

		GLFWimage images[1];
		
		std::string path = utils::FileSystem::getRootPath()+"/assets/icon/renderx.png";
		images[0].pixels = stbi_load(path.c_str(), &images[0].width, &images[0].height, 0, 4); //rgba channels 
		glfwSetWindowIcon(winSpeci.openglWinPtr, 1, images);
		stbi_image_free(images[0].pixels);

		glfwSetCursorPosCallback(winSpeci.openglWinPtr, [](GLFWwindow* window, double xPos, double yPos)
		{
			auto& winSpeci = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(window));
			
			event::MouseMovementEvent event((float)xPos, (float)yPos);
			winSpeci.onEvent(event);
			
			uint32_t navBarOffsetLeft = ui::MainGui::getOffsetNavItemLeft();
			uint32_t navBarOffsetRight = ui::MainGui::getOffsetNavItemRight();
			uint32_t navBarHeight = ui::MainGui::getNavbarHeight();

			int32_t leftSide = navBarOffsetLeft;
			int32_t rightSide = winSpeci.width - navBarOffsetRight;
			int32_t topSide = 0;
			int32_t bottomSide = navBarHeight;
			auto currMousePos = input::Mouse::getInstance()->getMouseCurrentPosition();

			if (input::Mouse::getInstance()->isLeftButtonPressed() && winSpeci.canMove) {
				auto cur = input::Mouse::getInstance()->getCursorPosRelativeToWindow();
				winSpeci.cursorOffsetX = xPos - cur.x;
				winSpeci.cursorOffsetY = yPos - cur.y;
			}
			
		});


		glfwSetKeyCallback(winSpeci.openglWinPtr, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto& data = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(window));
			static int repeatCount = 0;
			
			switch (action)
			{
			case GLFW_PRESS:
			{
				repeatCount = 1;
				event::KeyPressedEvent event(key, repeatCount);
				data.onEvent(event);
			
				break;
			}
			
			case GLFW_RELEASE:
			{
				repeatCount = 0;
				event::KeyReleasedEvent event(key);
				data.onEvent(event);
			
				break;
			}
			
			case GLFW_REPEAT:
			{
				repeatCount++;
				event::KeyPressedEvent event(key, repeatCount);
				data.onEvent(event);
				break;
			}
			}
		});


		glfwSetMouseButtonCallback(winSpeci.openglWinPtr, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& winSpeci = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(window));
			
			uint32_t navBarOffsetLeft = ui::MainGui::getOffsetNavItemLeft();
			uint32_t navBarOffsetRight = ui::MainGui::getOffsetNavItemRight();
			uint32_t navBarHeight = ui::MainGui::getNavbarHeight();

			int32_t leftSide = navBarOffsetLeft;
			int32_t rightSide = winSpeci.width - navBarOffsetRight;
			int32_t topSide = 0;
			int32_t bottomSide = navBarHeight;

			auto currMousePos = input::Mouse::getInstance()->getMouseCurrentPosition();

			switch (action)
			{
			case GLFW_PRESS:
			{
				event::MousePressedEvent event(button);
				winSpeci.onEvent(event);
				
				double x, y;
				glfwGetCursorPos(window, &x, &y);
				input::Mouse::getInstance()->setCursorPosRelativeToWindow(glm::vec2(x, y));

				if (currMousePos.x > leftSide && currMousePos.x <rightSide && currMousePos.y >topSide && currMousePos.y < bottomSide)
				{

					static auto before = std::chrono::system_clock::now();
					auto now = std::chrono::system_clock::now();
					double diff_ms = std::chrono::duration <double, std::milli>(now - before).count();
					before = now;
					if (diff_ms > 10 && diff_ms < 300) {
						//action = GLFW_DOUBLECLICK;
						// mDebug() << "doubleclick";
						std::cout << "double clicked" << std::endl;
						winSpeci.isDoubleClicked = true;

					}
					else
					{
						winSpeci.canMove = true;
					}


				}
				break;
			}
			
			case GLFW_RELEASE:
			{
				event::MouseReleasedEvent event(button);
				winSpeci.onEvent(event);

				if (currMousePos.x > leftSide && currMousePos.x <rightSide && currMousePos.y >topSide && currMousePos.y < bottomSide)
				{
					winSpeci.canMove = false;
					winSpeci.isDoubleClicked = false;


				}
				break;
			}
			}
		});

		glfwSetScrollCallback(winSpeci.openglWinPtr, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto& data = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(window));
			event::MouseScrollEvent event((float)xOffset, (float)yOffset);
			data.onEvent(event);
		});

		glfwMakeContextCurrent(winSpeci.openglWinPtr);


		glfwSetFramebufferSizeCallback(winSpeci.openglWinPtr, [](GLFWwindow* window, int width, int height) 
		{
			auto& data = *static_cast<WindowSpecification*>(glfwGetWindowUserPointer(window));
			data.framebufferWidth = width;
			data.framebufferHeight = height;
			glViewport(0, 0, width, height);
		});


		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		return true;
	}

	bool Window::isOpenglWinClose()
	{
		return glfwWindowShouldClose(winSpeci.openglWinPtr) == 0;
	}

	void Window::clear()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		setWindowSize();
		setWindowPos();
	}

	void Window::winSwapBuffer()
	{
		glfwSwapBuffers(winSpeci.openglWinPtr);
		glfwPollEvents();
	}

	void Window::setWindowSize()
	{
		if ((winSpeci.width != ui::MainGui::getMainUiWidth() || winSpeci.height != ui::MainGui::getMainUiHeight()) && ui::MainGui::isFullScreen())
		{
			winSpeci.width = ui::MainGui::getMainUiWidth();
			winSpeci.height = ui::MainGui::getMainUiHeight();
			glfwSetWindowSize(winSpeci.openglWinPtr, winSpeci.width, winSpeci.height);
			winSpeci.isFramebufferSizeChange = true;
		}
		else
		{
			winSpeci.isFramebufferSizeChange = false;
		}
	}

	void Window::setWindowPos()
	{

		if (input::Mouse::getInstance()->isLeftButtonPressed() && winSpeci.canMove && ui::MainGui::isFullScreen())
		{
			glfwGetWindowPos(winSpeci.openglWinPtr, &winSpeci.windowXPos, &winSpeci.windowYPos);
			glfwSetWindowPos(winSpeci.openglWinPtr, winSpeci.windowXPos + winSpeci.cursorOffsetX, winSpeci.windowYPos + winSpeci.cursorOffsetY);
			winSpeci.cursorOffsetX = 0;
			winSpeci.cursorOffsetY = 0;
		}
	}

	WindowSpecification Window::getWindowSpecification() const
	{
		return winSpeci;
	}

	WindowSpecification& Window::getWindowSpecificationRef()
	{
		return winSpeci;
	}

	void Window::destroyWindow()
	{
		glfwDestroyWindow(winSpeci.openglWinPtr);
	}
}