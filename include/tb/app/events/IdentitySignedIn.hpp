#ifndef TB_APP_EVENTS_IDENTITY_SIGNED_IN_EVENT_HPP
#define TB_APP_EVENTS_IDENTITY_SIGNED_IN_EVENT_HPP

#include <string>

namespace tb::app::events
{

struct IdentitySignedIn : public BaseUserEvent
{
public:
	explicit IdentitySignedIn(
		std::string identity_id,
		std::string email,
		std::string fname,
		std::string lname
	) : m_identityId(identity_id), m_email(email), m_firstName(fname), m_lastName(lname)
	{

	}

	inline const std::string& GetIdentityId() { return m_identityId; }
	inline const std::string& GetEmail() { return m_email; }
	inline const std::string& GetFirstName() { return m_firstName; }
	inline const std::string& GetLastName() { return m_lastName; }

	const char* GetName() const
	{
		return "IdentitySignedIn";
	}


private:
	std::string m_identityId;
	std::string m_email;
	std::string m_firstName;
	std::string m_lastName;

}; // cl IdentitySignedIn

} // ns tb::app::events

#endif