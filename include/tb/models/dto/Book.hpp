#ifndef TB_MODELS_DTO_BOOK_HPP
#define TB_MODELS_DTO_BOOK_HPP

#include <string>

namespace tb::models::dto
{

struct NewBookRequest
{
	std::string Name;

	std::string Description{ "" };

	std::string DefaultCurrencyIsoCode;

}; // st NewBookRequest


struct NewBookResponse
{
	std::string BookId;
}; // st NewBookResponse

} // ns tb::models::dto

#endif