#ifndef TB_APP_EVENTS_IDENTITY_SIGNED_OUT_EVENT_HPP
#define TB_APP_EVENTS_IDENTITY_SIGNED_OUT_EVENT_HPP

#include <string>

namespace tb::app::events
{

struct IdentitySignedOutEvent : public BaseUserEvent
{
public:
	explicit IdentitySignedOutEvent()
	{

	}
	const char* GetName() const
	{
		return "IdentitySignedOut";
	}

}; // cl IdentitySignedOut

} // ns tb::app::events

#endif