#pragma once
#include <common.h>
#include <glm/glm.hpp>
#include "event/mouse_event.h"

namespace engine::input
{
	enum MouseButtonType
	{
		RX_LEFT_BUTTON,
		RX_RIGHT_BUTTON,
		RX_MIDDLE_BUTTON
	};

	class Mouse
	{
	public:

		static std::shared_ptr<Mouse> getInstance();
		~Mouse();

		bool isLeftButtonPressed() const;
		bool isMidButtonPressed() const;
		bool isRightButtonPressed()	const;

		bool isLeftButtonReleased() const;
		bool isMidButtonReleased() const;
		bool isRightButtonReleased() const;


		const glm::vec2& getMouseLastPosiion() const;
		const glm::vec2& getMouseCurrentPosition() const;
		const glm::vec2& getMouseScrollOffset()const;

		void setMouseLastPosition(const glm::vec2& lastPosition);
		void setMouseCurrentPosition(const glm::vec2& currentPosition);
		void setMouseScrollOffset(const glm::vec2& scrollOffset);
		
		float getScrollSensitivity() const;
		float getMouseSensitivity() const;

		const glm::vec2& getMousePositionOffset()const;


		void onEvent(event::MouseMovementEvent& event);
		void onEvent(event::MousePressedEvent& event);
		void onEvent(event::MouseReleasedEvent& event);
		void onEvent(event::MouseScrollEvent& event);

		void updateMouse();

		void setCursorPosRelativeToWindow(const glm::vec2& curPos);
		glm::vec2 getCursorPosRelativeToWindow()const;


	private:
		Mouse();
		
	private:
		static std::shared_ptr<Mouse> s_instance;

		bool leftButton;
		bool midButton;
		bool rightButton;

		glm::vec2 cursorPositionRelativeToWindow;

		glm::vec2 lastPosition;
		glm::vec2 currentPosition;

		glm::vec2 scrollOffset;

		float scrollSensitivity;
		float mouseSensitivity;

	};
}