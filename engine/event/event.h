#pragma once
#include "common.h"

namespace engine::event
{
#define BIT(X) (1<<X)

	enum class EventType
	{
		RX_NONE_EVENT = 0,
		RX_WINDOW_RESIZE,
		RX_WINDOW_CLOSE,
		RX_WINDOW_MOVE,
		RX_MOUSE_MOVE,
		RX_MOUSE_BUTTON,
		RX_MOUSE_PRESS,
		RX_MOUSE_RELEASE,
		RX_MOUSE_SCROLL,
		RX_KEYBOARD,
		RX_KEY_PRESS,
		RX_KEY_RELEASE,
		RX_KEY_TYPE
	};

	enum EventCategory
	{
		RX_NONE_CG = 0,
		RX_EVENT_CATEGORY_INPUT = BIT(0),
		RX_EVENT_CATEGORY_MOUSE = BIT(1),
		RX_EVENT_CATEGORY_MOUSE_BUTTON = BIT(2),
		RX_EVENT_CATEGORY_KEYBOARD = BIT(3),
		RX_EVENT_CATEGORY_WINDOW = BIT(4),
		RX_EVENT_CATEGORY_GUI = BIT(5)
	};

	class Event
	{
	public:
		friend class EventDispatcher;
		Event();
		virtual ~Event();

		static EventType getStaticEventType();
		virtual EventType getEventType() const = 0;
		virtual const char* getEventName() const = 0;
		virtual int getCategoryFlags() const = 0;

		bool isInCategory(EventCategory category);

	protected:
		bool isEventHandled;
	};


#define EVENT_CLASS_TYPE(type) static EventType getStaticEventType() {return EventType::##type;}\
		virtual EventType getEventType() const override { return getStaticEventType(); }

#define EVENT_NAME_TYPE(type) virtual const char* getEventName() const override { return #type; }

#define EVENT_CATEGORY_TYPE(category) virtual int getCategoryFlags()const override { return category; }

}