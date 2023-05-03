#include "mouse_event.h"

namespace engine::event
{
	MouseMovementEvent::MouseMovementEvent(float xpos, float ypos)
		:xpos(xpos),ypos(ypos)
	{
	}

	MouseMovementEvent::~MouseMovementEvent()
	{
	}

	float MouseMovementEvent::getMouseXpos() const
	{
		return xpos;
	}

	float MouseMovementEvent::getMouseYpos() const
	{
		return ypos;
	}

	
	MouseScrollEvent::MouseScrollEvent(float xOffset, float yOffset)
		:xOffset(xOffset), yOffset(yOffset)
	{

	}


	MouseScrollEvent::~MouseScrollEvent()
	{

	}

	float MouseScrollEvent::getMouseScrollXOffset() const
	{
		return xOffset;
	}

	float MouseScrollEvent::getMouseScrollYOffset() const
	{
		return yOffset;
	}

	MouseButtonEvent::MouseButtonEvent(uint32_t button)
		:mouseButton(button)
	{
	}

	MouseButtonEvent::~MouseButtonEvent()
	{
	}

	uint32_t MouseButtonEvent::getMouseButton() const
	{
		return mouseButton;
	}

	MouseReleasedEvent::MouseReleasedEvent(uint32_t button)
		:MouseButtonEvent(button)
	{
	}

	MouseReleasedEvent::~MouseReleasedEvent()
	{
	}

	MousePressedEvent::MousePressedEvent(uint32_t button)
		:MouseButtonEvent(button)
	{
	}

	MousePressedEvent::~MousePressedEvent()
	{
	}

}