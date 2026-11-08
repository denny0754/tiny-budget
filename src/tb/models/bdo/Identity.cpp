#include <tb/models/bdo/Identity.hpp>

namespace tb::models::bdo
{

Identity::Identity(
	const std::string& guid,
	const std::chrono::system_clock::time_point& created_on,
	const std::chrono::system_clock::time_point& updated_on,
	const std::string& email,
	const std::string& first_name,
	const std::string& last_name
)
	: tb::models::bdo::BaseDataObject(guid, created_on, updated_on),
	m_email(email), m_firstName(first_name), m_lastName(last_name)
{

}

const std::string& Identity::GetEmail() const
{
	return m_email;
}

const std::string& Identity::GetFirstName() const
{
	return m_firstName;
}

const std::string& Identity::GetLastName() const
{
	return m_lastName;
}

const std::string& Identity::GetFormattedName() const
{
	return std::format("{} {}", m_firstName, m_lastName);
}

} // ns tb::models::bdo