/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#ifndef TB_MODELS_DTO_BOOK_HPP
#define TB_MODELS_DTO_BOOK_HPP

#include <tb/models/dto/Common.hpp>

#include <string>

namespace tb::models::dto
{

struct GetBookResponseData
{
	std::string Guid;

	std::string Name;

	std::string Description;

	std::string CurrencyGuid;
}; // st GetBookResponse

struct CreateBookRequest
{
	std::string Name;

	std::string Description{ "" };

	std::string DefaultCurrencyIsoCode;

}; // st CreateBookRequest


struct CreateBookResponseData
{
	std::string Guid;
}; // st CreateBookResponseData

struct UpdateBookRequest
{
	std::string Name;

	std::string Description;

	std::string CurrencyGuid;
}; // st UpdateBookRequest

struct UpdateBookResponseData
{
	std::string Guid;

	std::string Name;

	std::string Description;

	std::string CurrencyGuid;
}; // st UpdateBookResponseData

struct DeleteBookResponseData
{
	// Empty response data.
}; // st DeleteBookResponseData

using GetBookResponse = tb::models::dto::APIResponse<GetBookResponseData>;
using CreateBookResponse = tb::models::dto::APIResponse <CreateBookResponseData>;
using UpdateBookResponse = tb::models::dto::APIResponse <UpdateBookResponseData>;
using DeleteBookResponse = tb::models::dto::APIResponse <DeleteBookResponseData>;

} // ns tb::models::dto

#endif