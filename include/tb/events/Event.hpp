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

struct SystemEvent : public Event
{
public:
	virtual const char* GetName() = 0;

	virtual ~SystemEvent() = default;
};

struct SessionEvent : public Event
{
public:
	virtual const char* GetName() = 0;

	virtual ~SessionEvent() = default;
};


struct UserInterfaceEvent : public Event
{
public:
	virtual const char* GetName() = 0;

	virtual ~UserInterfaceEvent() = default;
};


} // tb::events

#endif