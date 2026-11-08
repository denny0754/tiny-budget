#ifndef TB_MODELS_DTO_BOOK_HPP
#define TB_MODELS_DTO_BOOK_HPP

#include <string>

namespace tb::models::dto
{

struct GetBookResponse
{
	std::string Id;

	std::string Name;

	std::string Description;

	std::string DefaultCurrencyLabel;

	std::string DefaultCurrencyIsoCode;
}; // st GetBookResponse

struct CreateBookRequest
{
	std::string Name;

	std::string Description{ "" };

	std::string DefaultCurrencyIsoCode;

}; // st NewBookRequest


struct CreateBookResponse
{
	std::string Id;
}; // st NewBookResponse


struct UpdateBookRequest
{
	std::string Id;

	std::string Name;

	std::string Description;

	std::string DefaultCurrencyIsoCode;
}; // st UpdateBookRequest

struct UpdateBookResponse
{
	std::string Id;

	std::string Name;

	std::string Description;

	std::string DefaultCurrencyIsoCode;
}; // st UpdateBookResponse


} // ns tb::models::dto

#endif