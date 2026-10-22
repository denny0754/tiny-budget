#ifndef TB_EVENTS_UI_PUSH_GLOBAL_COMPONENT_EVENT_HPP
#define TB_EVENTS_UI_PUSH_GLOBAL_COMPONENT_EVENT_HPP

#include <tb/events/Event.hpp>

namespace tb::events
{

class PushGlobalComponentEvent : public tb::events::UserInterfaceEvent
{
public:
	const char* GetName() override { return "PushGlobalComponentEvent"; }
};

} // ns tb::events

#endif