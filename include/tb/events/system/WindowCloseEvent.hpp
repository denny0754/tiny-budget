#ifndef TB_EVENTS_SYSTEM_WINDOW_CLOSE_EVENT_HPP
#define TB_EVENTS_SYSTEM_WINDOW_CLOSE_EVENT_HPP

#include <tb/events/Event.hpp>

namespace tb::events
{

class WindowCloseEvent : public tb::events::SystemEvent
{
public:
	const char* GetName() override { return "WindowCloseEvent"; }
}; // cl WindowCloseEvent

} // ns tb::events

#endif