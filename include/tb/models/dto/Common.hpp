#ifndef TB_MODELS_DTO_COMMON_HPP
#define TB_MODELS_DTO_COMMON_HPP

#include <string>
#include <functional>

namespace tb::models::dto
{

template<typename T>
struct APIResult
{
	std::string ErrorMessage{};
	bool Success;

	T Result;
}; // st APIResult

template<typename T>
using APICallback = std::function<void(const tb::models::dto::APIResult<T>&)>;

} // ns tb::models::dto

#endif