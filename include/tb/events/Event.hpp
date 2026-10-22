#ifndef TB_EVENTS_EVENT_HPP
#define TB_EVENTS_EVENT_HPP

namespace tb::events
{

struct Event
{
public:
	virtual ~Event() = default;

	virtual const char* GetName() = 0;

	mutable bool Handled{ false };

}; // cl Event

struct SystemEvent : public Event {};
struct SessionEvent : public Event {};
struct UserInterfaceEvent : public Event {};

} // tb::events

#endif