#ifndef TB_MODELS_DTO_AUTHENTICATION_HPP
#define TB_MODELS_DTO_AUTHENTICATION_HPP

#include <string>

namespace tb::models::dto
{

struct SignUpRequest
{
	std::string Email;

	std::string Password;

	std::string FirstName;

	std::string LastName;
};

struct SignInRequest
{
	std::string Email;

	std::string Password;
};

struct SignUpResponse
{
	// TODO
};

struct SignInResponse
{
	// TODO
};

} // ns tb::models::dto

#endif