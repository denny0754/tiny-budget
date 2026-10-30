#ifndef TB_EVENTS_IDENTITY_SIGNED_OUT_EVENT_HPP
#define TB_EVENTS_IDENTITY_SIGNED_OUT_EVENT_HPP

#include <tb/events/Event.hpp>
#include <string>

namespace tb::events
{

struct IdentitySignedOutEvent : public tb::events::SessionEvent
{
public:
	explicit IdentitySignedOutEvent(
		std::string identity_id,
		std::string email
	) : m_identityId(identity_id), m_email(email)
	{

	}

	inline const std::string& GetIdentityId() const { return m_identityId; }
	inline const std::string& GetEmail() const { return m_email; }

	const char* GetName() const
	{
		return "IdentitySignedOut";
	}


private:
	std::string m_identityId;
	std::string m_email;

}; // cl IdentitySignedOut

} // ns tb::events

#endif