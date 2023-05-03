#include "input_manager.h"
#include "event/event_dispatcher.h"

namespace engine::input
{
	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::onEvent(event::Event& event)
	{
		bool eventHandled = false;
		event::EventDispatcher dispatcher(event);
		
		if (event.isInCategory(event::RX_EVENT_CATEGORY_KEYBOARD))
		{
			if (!eventHandled)
			{
				eventHandled = dispatcher.dispatchEvent<event::KeyPressedEvent>(BIND_EVENT(InputManager::onKeyPressedEvent));
			}

			if (!eventHandled)
			{
				eventHandled = dispatcher.dispatchEvent<event::KeyReleasedEvent>(BIND_EVENT(InputManager::onKeyReleasedEvent));
			}

		}
		else if (event.isInCategory(event::RX_EVENT_CATEGORY_MOUSE))
		{
			if (!eventHandled)
			{
				eventHandled = dispatcher.dispatchEvent<event::MouseMovementEvent>(BIND_EVENT(InputManager::onMouseMovementEvent));
			}

			if (!eventHandled)
			{
				eventHandled = dispatcher.dispatchEvent<event::MousePressedEvent>(BIND_EVENT(InputManager::onMouseButtonPressed));
			}

			if (!eventHandled)
			{
				eventHandled = dispatcher.dispatchEvent<event::MouseReleasedEvent>(BIND_EVENT(InputManager::onMouseButtonReleased));
			}

			if (!eventHandled)
			{
				eventHandled = dispatcher.dispatchEvent<event::MouseScrollEvent>(BIND_EVENT(InputManager::onMouseScrollEvent));
			}
		}
		
	}

	bool InputManager::onMouseMovementEvent(event::MouseMovementEvent& event)
	{
		Mouse::getInstance()->onEvent(event);
		return true;
	}

	bool InputManager::onMouseButtonPressed(event::MousePressedEvent& event)
	{
		Mouse::getInstance()->onEvent(event);
		return true;
	}

	bool InputManager::onMouseButtonReleased(event::MouseReleasedEvent& event)
	{
		Mouse::getInstance()->onEvent(event);
		return true;
	}

	bool InputManager::onMouseScrollEvent(event::MouseScrollEvent& event)
	{
		Mouse::getInstance()->onEvent(event);
		return true;
	}

	bool InputManager::onKeyPressedEvent(event::KeyPressedEvent& event)
	{
		Keyboard::getInstance()->onEvent(event);
		return true;
	}

	bool InputManager::onKeyReleasedEvent(event::KeyReleasedEvent& event)
	{
		Keyboard::getInstance()->onEvent(event);
		return true;
	}
	
}