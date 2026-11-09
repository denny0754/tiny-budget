/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#ifndef TB_API_CURRENCY_CLIENT_HPP
#define TB_API_CURRENCY_CLIENT_HPP

#include <tb/api/Client.hpp>
#include <tb/models/dto/Common.hpp>
#include <tb/models/dto/Currency.hpp>

namespace tb::api
{

class CurrencyClient : public tb::api::Client
{
public:
	CurrencyClient(const std::shared_ptr<tb::core::SessionContext>& ctx,
		const std::shared_ptr<Wt::Dbo::Session>& db)
		: tb::api::Client(ctx, db)
	{

	}

	tb::models::dto::CreateCurrencyResponse Create(
		const tb::models::dto::CreateCurrencyRequest& data
	);

	tb::models::dto::UpdateCurrencyResponse UpdateById(
		const std::string& id,
		const tb::models::dto::UpdateCurrencyRequest& data
	);

	tb::models::dto::UpdateCurrencyResponse UpdateByIsoCode(
		const std::string& iso_code,
		const tb::models::dto::UpdateCurrencyRequest& data
	);

	tb::models::dto::DeleteCurrencyResponse Delete(
		const std::string& id
	);

	tb::models::dto::GetCurrencyResponse GetById(
		const std::string& id
	);

	tb::models::dto::GetCurrencyResponse GetByIsoCode(
		const std::string& isoCode
	);

	tb::models::dto::GetCurrencyResponse GetAny(
		//TODO: Add query parameters
	);

}; // cl CurrencyClient

} // ns tb::api

#endif