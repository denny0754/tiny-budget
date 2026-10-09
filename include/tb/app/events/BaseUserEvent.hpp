#ifndef TB_APP_EVENTS_USER_EVENT_HPP
#define TB_APP_EVENTS_USER_EVENT_HPP

#include <string>

namespace tb::app::events
{

struct BaseUserEvent
{
public:
	virtual ~BaseUserEvent() = default;

	mutable bool Handled{ false };

	virtual const char* GetName() const = 0;

	virtual std::string ToString() const {
		return GetName();
	}
}; // st UserEvent

} // ns tb::app::events

#endif