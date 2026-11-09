/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#ifndef TB_MODELS_DTO_CURRENCY_HPP
#define TB_MODELS_DTO_CURRENCY_HPP

#include <tb/models/dto/Common.hpp>

#include <string>

namespace tb::models::dto
{

struct GetCurrencyResponseData
{
	std::string Guid;

	std::string IsoCode;

	std::string Label;

	std::string Symbol;

}; // st GetCurrencyResponseData

struct CreateCurrencyRequest
{
	std::string IsoCode;

	std::string Label;

	std::string Symbol;
}; // st CreateCurrencyRequest

struct CreateCurrencyResponseData
{
	std::string Guid;

	std::string IsoCode;

	std::string Label;

	std::string Symbol;
}; // st CreateCurrencyResponseData

struct UpdateCurrencyRequest
{
	std::string IsoCode;

	std::string Label;

	std::string Symbol;
}; // st UpdateCurrencyRequest

struct UpdateCurrencyResponseData
{
	std::string Guid;

	std::string IsoCode;

	std::string Label;

	std::string Symbol;
}; // st UpdateCurrencyResponseData

struct DeleteCurrencyResponseData
{
	// Empty response data.
}; // st DeleteCurrencyResponseData

// Template Initialization
using GetCurrencyResponse = tb::models::dto::APIResponse<GetCurrencyResponseData>;
using CreateCurrencyResponse = tb::models::dto::APIResponse <CreateCurrencyResponseData>;
using UpdateCurrencyResponse = tb::models::dto::APIResponse <UpdateCurrencyResponseData>;
using DeleteCurrencyResponse = tb::models::dto::APIResponse <DeleteCurrencyResponseData>;

} // ns tb::models::dto

#endif