#ifndef TB_MODELS_DTO_COMMON_HPP
#define TB_MODELS_DTO_COMMON_HPP

#include <string>
#include <functional>
#include <unordered_map>

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
using PaginatedAPIResult = APIResult<std::vector<T>>;

template<typename T>
using APICallback = std::function<void(const tb::models::dto::APIResult<T>&)>;

template<typename T>
using PaginatedAPICallback = std::function<void(const tb::models::dto::PaginatedAPIResult<T>&)>;

struct APIQueryParams
{
	unsigned int Page{ 0 };

	unsigned int PageSize{ 100 };

	std::unordered_map<std::string, std::string> Filters{};
};



} // ns tb::models::dto

#endif