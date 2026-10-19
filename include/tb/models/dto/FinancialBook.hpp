#ifndef TB_MODELS_DTO_HPP
#define TB_MODELS_DTO_HPP

namespace tb::models::dto
{

struct CreateFinancialBookRequest
{

	std::string Name;

	std::string DefaultCurrency;

}; // st CreateFinancialBookRequest

struct CreateFinancialBookResponse
{
	std::string FinancialBookId;
};

} // ns tb::models::dto

#endif