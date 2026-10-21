#ifndef TB_API_SESSION_CONTEXT
#define TB_API_SESSION_CONTEXT

#include <string>

namespace tb::api
{

struct SessionContext
{
	std::string FirstName;

	std::string LastName;

	std::string Email;

	std::string IdentityId;

	std::string CurrentFinancialBookId;

	void Clear()
	{
		this->FirstName = std::string("");
		this->LastName = std::string("");
		this->Email = std::string("");
		this->IdentityId = std::string("");
		this->CurrentFinancialBookId = std::string("");

	}
};

} // ns tb::api

#endif