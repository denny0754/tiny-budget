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

} // ns tb::models::dto

#endif