#pragma once
#include "event.h"

namespace engine::event
{
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) :event(event) {}
		~EventDispatcher() {}

		template<class T>
		bool dispatchEvent(std::function<bool(T&)> eventFunc)
		{
			if (!event.isEventHandled && event.getEventType() == T::getStaticEventType())
			{

				event.isEventHandled = eventFunc(*(T*)&event);
				return true;
			}

			return false;
		}

	private:
		Event& event;
	};
}