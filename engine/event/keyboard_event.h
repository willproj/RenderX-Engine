#pragma once
#include "event.h"


namespace engine::event
{
	class KeyboardEvent :public Event
	{
	public:

		KeyboardEvent(int32_t keyCode);
		~KeyboardEvent();
		
		int32_t getKeyCode()const;

		EVENT_CLASS_TYPE(RX_KEYBOARD)
		EVENT_NAME_TYPE(RX_KEYBOARD)
		EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_KEYBOARD | RX_EVENT_CATEGORY_INPUT)

	protected:
		int32_t keyCode;
	};


	class KeyPressedEvent :public KeyboardEvent
	{
	public:
		KeyPressedEvent(int32_t keyCode, int32_t keyRepeatCount);
		~KeyPressedEvent();
		
		int32_t getKeyRepeatCount()const;

		EVENT_CLASS_TYPE(RX_KEY_PRESS)
		EVENT_NAME_TYPE(RX_KEY_PRESS)

	private:
		int32_t keyRepeatCount;
	};

	class KeyReleasedEvent :public KeyboardEvent
	{
	public:
		KeyReleasedEvent(int32_t keyCode);
		~KeyReleasedEvent();
		
		EVENT_CLASS_TYPE(RX_KEY_RELEASE)
		EVENT_NAME_TYPE(RX_KEY_RELEASE)

	};
}