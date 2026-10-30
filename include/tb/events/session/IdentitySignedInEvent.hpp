#ifndef TB_EVENTS_IDENTITY_SIGNED_IN_EVENT_HPP
#define TB_EVENTS_IDENTITY_SIGNED_IN_EVENT_HPP

#include <tb/events/Event.hpp>
#include <string>

namespace tb::events
{

struct IdentitySignedInEvent : public tb::events::SessionEvent
{
public:
	explicit IdentitySignedInEvent(
		std::string identity_id,
		std::string email,
		std::string fname,
		std::string lname
	) : m_identityId(identity_id), m_email(email), m_firstName(fname), m_lastName(lname)
	{

	}

	~IdentitySignedInEvent() = default;

	inline const std::string& GetIdentityId() const { return m_identityId; }
	inline const std::string& GetEmail() const { return m_email; }
	inline const std::string& GetFirstName() const { return m_firstName; }
	inline const std::string& GetLastName() const { return m_lastName; }

	const char* GetName() override
	{
		return "IdentitySignedIn";
	}


private:
	std::string m_identityId;
	std::string m_email;
	std::string m_firstName;
	std::string m_lastName;

}; // cl IdentitySignedIn

} // ns tb::events

#endif