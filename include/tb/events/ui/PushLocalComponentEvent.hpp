#ifndef TB_EVENTS_UI_PUSH_LOCAL_COMPONENT_EVENT_HPP
#define TB_EVENTS_UI_PUSH_LOCAL_COMPONENT_EVENT_HPP

#include <tb/events/Event.hpp>

namespace tb::events
{

class PushLocalComponentEvent: public tb::events::UserInterfaceEvent
{
public:
	const char* GetName() override { return "PushLocalComponentEvent"; }
};

} // ns tb::events

#endif