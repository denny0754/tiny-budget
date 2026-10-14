#ifndef TB_APP_EVENTS_IDENTITY_SIGNED_OUT_EVENT_HPP
#define TB_APP_EVENTS_IDENTITY_SIGNED_OUT_EVENT_HPP

#include <string>

namespace tb::app::events
{

struct IdentitySignedOut : public BaseUserEvent
{
public:
	explicit IdentitySignedOut()
	{

	}
	const char* GetName() const
	{
		return "IdentitySignedOut";
	}

}; // cl IdentitySignedOut

} // ns tb::app::events

#endif