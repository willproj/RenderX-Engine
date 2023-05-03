#include "event.h"

namespace engine::event
{
	Event::Event()
		:isEventHandled(false)
	{

	}


	Event::~Event()
	{

	}

	EventType Event::getStaticEventType()
	{
		return EventType::RX_NONE_EVENT;
	}

	bool Event::isInCategory(EventCategory category)
	{
		return getCategoryFlags() & category;
	}

}