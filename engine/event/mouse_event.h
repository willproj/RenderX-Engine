#pragma once
#include "event.h"

namespace engine::event
{
	class MouseMovementEvent :public Event
	{
	public:
		MouseMovementEvent(float xpos, float ypos);
		~MouseMovementEvent();

		float getMouseXpos()const;
		float getMouseYpos()const;

		EVENT_CLASS_TYPE(RX_MOUSE_MOVE)
		EVENT_NAME_TYPE(RX_MOUSE_MOVE)
		EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_MOUSE | RX_EVENT_CATEGORY_INPUT);

	private:
		float xpos, ypos;
	};


	class MouseScrollEvent :public Event
	{
	public:
		MouseScrollEvent(float xOffset, float yOffset);
		~MouseScrollEvent();

		float getMouseScrollXOffset()const;
		float getMouseScrollYOffset()const;

		EVENT_CLASS_TYPE(RX_MOUSE_SCROLL)
		EVENT_NAME_TYPE(RX_MOUSE_SCROLL)
		EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_MOUSE | RX_EVENT_CATEGORY_INPUT);

	private:
		float xOffset, yOffset;
	};


	class MouseButtonEvent :public Event
	{
	public:
		MouseButtonEvent(uint32_t button);
		~MouseButtonEvent();
		uint32_t getMouseButton() const;

		EVENT_CLASS_TYPE(RX_MOUSE_BUTTON)
		EVENT_NAME_TYPE(RX_MOUSE_BUTTON)
		EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_MOUSE | RX_EVENT_CATEGORY_MOUSE_BUTTON | RX_EVENT_CATEGORY_INPUT)
	protected:
		uint32_t mouseButton;
	};

	class MousePressedEvent :public MouseButtonEvent
	{
	public:
		MousePressedEvent(uint32_t button);
		~MousePressedEvent();

		EVENT_CLASS_TYPE(RX_MOUSE_PRESS)
		EVENT_NAME_TYPE(RX_MOUSE_PRESS)
	};

	class MouseReleasedEvent :public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(uint32_t button);
		~MouseReleasedEvent();

		EVENT_CLASS_TYPE(RX_MOUSE_RELEASE)
		EVENT_NAME_TYPE(RX_MOUSE_RELEASE)
	};
}