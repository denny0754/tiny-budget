#ifndef TB_MODELS_DTO_CURRENCY_HPP
#define TB_MODELS_DTO_CURRENCY_HPP

#include <string>

namespace tb::models::dto
{

struct GetCurrencyResponse
{

	std::string Id;

	std::string IsoCode;

	std::string Label;

	std::string Symbol;

}; // st GetCurrencyResponse

struct CreateCurrencyRequest
{
	std::string IsoCode;

	std::string Label;

	std::string Symbol;
};

struct CreateCurrencyResponse
{
	std::string Id;
};

struct UpdateCurrencyRequest
{
	std::string IsoCode;

	std::string Label;

	std::string Symbol;
};

struct UpdateCurrencyResponse
{
	std::string IsoCode;

	std::string Label;

	std::string Symbol;
};

struct DeleteCurrencyResponse { };

} // ns tb::models::dto

#endif