#ifndef TB_CORE_MODELS_DTO_AUTH_HPP
#define TB_CORE_MODELS_DTO_AUTH_HPP

#include "core/models/dto/Common.hpp"

namespace tb::dto
{

struct SignUpCommand
{
	std::string first_name;

	std::string last_name;

	std::string email;

	std::string password;
}; // st SignUpCommand

struct SignInCommand
{
	std::string email;

	std::string email;
}; // st SignInCommand

} // ns tb::dto

#endif