#ifndef TB_MODELS_DTO_HPP
#define TB_MODELS_DTO_HPP

#include <string>

namespace tb::models::dto
{

struct CreateFinancialBookRequest
{
	std::string Name;

	std::string Description;

	std::string DefaultCurrencyCode;

}; // st CreateFinancialBookRequest

struct CreateFinancialBookResponse
{
	std::string FinancialBookId;
}; // st CreateFinancialBookResponse

struct GetFinancialBookResponse
{
	std::string Id;

	std::string Name;

	std::string Description;

	std::string DefaultCurrencyCode;
}; // st GetFinancialBookResponse

} // ns tb::models::dto

#endif