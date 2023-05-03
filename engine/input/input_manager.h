#pragma once
#include "keyboard.h"
#include "mouse.h"
#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

namespace engine::input
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void onEvent(event::Event& event);

		bool onMouseMovementEvent(event::MouseMovementEvent& event);
		bool onMouseButtonPressed(event::MousePressedEvent& event);
		bool onMouseButtonReleased(event::MouseReleasedEvent& event);
		bool onMouseScrollEvent(event::MouseScrollEvent& event);

		bool onKeyPressedEvent(event::KeyPressedEvent& event);
		bool onKeyReleasedEvent(event::KeyReleasedEvent& event);

	private:
		std::shared_ptr<Keyboard> s_keyboardInstance;
		std::shared_ptr<Mouse> s_mouseInstance;
	};
}