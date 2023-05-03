#include "mouse.h"

namespace engine::input
{
	std::shared_ptr<Mouse> Mouse::s_instance;

	std::shared_ptr<Mouse> Mouse::getInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = std::shared_ptr<Mouse>(new Mouse());
		}
		return s_instance;
	}

	Mouse::Mouse()
		:lastPosition(glm::vec2(0.0f)),
		currentPosition(glm::vec2(0.0f)),
		mouseSensitivity(0.1f),
		scrollSensitivity(0.08f),
		scrollOffset(glm::vec2(0.0f)),
		leftButton(false),
		midButton(false),
		rightButton(false)	
	{

	}

	Mouse::~Mouse()
	{

	}


	bool Mouse::isLeftButtonPressed() const
	{
		return leftButton == true;
	}

	bool Mouse::isMidButtonPressed() const
	{
		return midButton == true;
	}

	bool Mouse::isRightButtonPressed()	const
	{
		return rightButton == true;
	}


	bool Mouse::isLeftButtonReleased() const
	{
		return leftButton == false;
	}

	bool Mouse::isMidButtonReleased() const
	{
		return midButton == false;
	}

	bool Mouse::isRightButtonReleased() const
	{
		return rightButton == false;
	}
	

	glm::vec2 Mouse::getMouseLastPosiion() const
	{
		return lastPosition;
	}

	glm::vec2 Mouse::getMouseCurrentPosition() const
	{
		return currentPosition;
	}

	glm::vec2 Mouse::getMouseScrollOffset()const
	{
		return scrollOffset;
	}

	void Mouse::setMouseLastPosition(const glm::vec2& lastPosition)
	{
		this->lastPosition = lastPosition;
	}

	void Mouse::setMouseCurrentPosition(const glm::vec2& currentPosition)
	{
		this->currentPosition = currentPosition;
	}

	void Mouse::setMouseScrollOffset(const glm::vec2& scrollOffset)
	{
		this->scrollOffset = scrollOffset;
	}

	float Mouse::getScrollSensitivity() const
	{
		return scrollSensitivity;
	}

	float Mouse::getMouseSensitivity() const
	{
		return mouseSensitivity;
	}

	glm::vec2 Mouse::getMousePositionOffset() const
	{
		return currentPosition - lastPosition;
	}

	void Mouse::setCursorPosRelativeToWindow(const glm::vec2& curPos)
	{
		cursorPositionRelativeToWindow = curPos;
	}

	glm::vec2 Mouse::getCursorPosRelativeToWindow()const
	{
		return cursorPositionRelativeToWindow;
	}

	void Mouse::onEvent(event::MouseMovementEvent& event)
	{
		lastPosition = currentPosition;

		//float xoffset = event.getMouseXpos() - lastPosition.x;
		//float yoffset = event.getMouseYpos() - lastPosition.y;
		//
		//xoffset *= mouseSensitivity;
		//yoffset *= mouseSensitivity;
		//
		//currentPosition.x += xoffset;
		//currentPosition.y += yoffset;

		currentPosition.x = event.getMouseXpos();
		currentPosition.y = event.getMouseYpos();
	}

	void Mouse::onEvent(event::MousePressedEvent& event)
	{
		if (event.getMouseButton() == MouseButtonType::RX_LEFT_BUTTON)
		{
			leftButton = true;
		}
		else if (event.getMouseButton() == MouseButtonType::RX_MIDDLE_BUTTON)
		{
			midButton = true;
		}
		else if (event.getMouseButton() == MouseButtonType::RX_RIGHT_BUTTON)
		{
			rightButton = true;
		}

	}

	void Mouse::onEvent(event::MouseReleasedEvent& event)
	{
		if (event.getMouseButton() == MouseButtonType::RX_LEFT_BUTTON)
		{
			leftButton = false;
		}
		else if (event.getMouseButton() == MouseButtonType::RX_MIDDLE_BUTTON)
		{
			midButton = false;
		}
		else if (event.getMouseButton() == MouseButtonType::RX_RIGHT_BUTTON)
		{
			rightButton = false;
		}
	}

	void Mouse::onEvent(event::MouseScrollEvent& event)
	{
		float xoffset = event.getMouseScrollXOffset() * scrollSensitivity;
		float yoffset = event.getMouseScrollYOffset() * scrollSensitivity;

		scrollOffset = glm::vec2(xoffset, yoffset);
	}

	void Mouse::updateMouse()
	{
		lastPosition = currentPosition;
		scrollOffset = glm::vec2(0.0f);
	}
}