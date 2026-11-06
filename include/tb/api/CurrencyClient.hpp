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

	void GetCurrency(
		tb::models::dto::APIQueryParams params,
		tb::models::dto::PaginatedAPIResult<tb::models::dto::GetCurrencyResponse> result
	);

}; // cl CurrencyClient

} // ns tb::api

#endif