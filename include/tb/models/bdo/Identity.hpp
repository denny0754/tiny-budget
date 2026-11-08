#ifndef TB_MODELS_BDO_IDENTITY_HPP
#define TB_MODELS_BDO_IDENTITY_HPP

#include <tb/models/bdo/Common.hpp>

#include <string>

namespace tb::models::bdo
{

class Identity : public tb::models::bdo::BaseDataObject
{
public:
	Identity(
		const std::string& guid,
		const std::chrono::system_clock::time_point& created_on,
		const std::chrono::system_clock::time_point& updated_on,
		const std::string& email,
		const std::string& first_name,
		const std::string& last_name
	);

	const std::string& GetEmail() const;

	const std::string& GetFirstName() const;

	const std::string& GetLastName() const;

	const std::string& GetFormattedName() const;

private:
	std::string m_email;
	std::string m_firstName;
	std::string m_lastName;
}; // cl Identity

} // ns tb::models::bdo

#endif