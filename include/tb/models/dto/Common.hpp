#ifndef TB_MODELS_DTO_COMMON_HPP
#define TB_MODELS_DTO_COMMON_HPP

#include <string>

namespace tb::models::dto
{

template<typename T>
struct APIResult
{
	std::string ErrorMessage{};
	bool Success;

	T Result;
}; // st APIResult

} // ns tb::models::dto

#endif