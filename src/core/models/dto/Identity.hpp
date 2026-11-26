#ifndef TB_CORE_MODELS_DTO_IDENTITY_HPP
#define TB_CORE_MODELS_DTO_IDENTITY_HPP

#include <string>

namespace tb::dto
{

struct Identity
{
	std::string guid;

	std::string first_name;

	std::string last_name;

	std::string email;
}; // st Identity

} // ns tb::dto

#endif