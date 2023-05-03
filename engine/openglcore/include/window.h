#pragma once
#include "thirdparty_header.h"

#include "event/mouse_event.h"
#include "event/keyboard_event.h"


namespace engine::openglcore
{
	struct WindowSpecification
	{
		uint32_t width;
		uint32_t height;
		std::string title;

		int32_t windowXPos = 0;
		int32_t windowYPos = 0;

		int32_t cursorOffsetX = 0;
		int32_t cursorOffsetY = 0;
		

		bool canMove = false;

		GLFWwindow* openglWinPtr;

		std::function<void(event::Event&)> eventCallbackFunc;

		void onEvent(event::Event& event)
		{
			if (eventCallbackFunc)
			{
				eventCallbackFunc(event);
			}
		}

	};


	class Window
	{
	public:
		~Window();

		static std::shared_ptr<Window> getInstance();

		bool isOpenglWinClose();

		bool init();
		void clear();

		GLFWwindow* getGLFWwinPtr() { return winSpeci.openglWinPtr; }
		int getWidth()const { return winSpeci.width; }
		int getHeight()const { return winSpeci.height; }

		void winSwapBuffer();
		void destroyWindow();
		void setWindowPos(uint32_t xpos, uint32_t ypos);
		void setEventCallbackFunc(const std::function<void(event::Event&)>& eventCallbackFunc);
		void setWindowSize();
		void setWindowPos();

	private:

		Window();
		static std::shared_ptr<Window> s_Instance;
		void windowPosCallback(GLFWwindow* window, uint32_t xpos, uint32_t ypos);
	private:
		WindowSpecification winSpeci;
	};
}
