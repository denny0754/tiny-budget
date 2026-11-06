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

	void Create(
		const tb::models::dto::CreateCurrencyRequest& data,
		tb::models::dto::APICallback<tb::models::dto::CreateCurrencyResponse> callback
	);

	void UpdateById(
		const std::string& id,
		const tb::models::dto::UpdateCurrencyRequest& data,
		tb::models::dto::APICallback<tb::models::dto::UpdateCurrencyResponse> callback
	);

	void UpdateByIsoCode(
		const std::string& id,
		const tb::models::dto::UpdateCurrencyRequest& data,
		tb::models::dto::APICallback<tb::models::dto::UpdateCurrencyResponse> callback
	);

	void DeleteById(
		const std::string& id,
		tb::models::dto::APICallback<tb::models::dto::DeleteCurrencyResponse> callback
	);

	void DeleteByIsoCode(
		const std::string& isoCode,
		tb::models::dto::APICallback<tb::models::dto::DeleteCurrencyResponse> callback
	);

	void GetById(
		const std::string& id,
		tb::models::dto::APICallback<tb::models::dto::GetCurrencyResponse> callback
	);

	void GetByIsoCode(
		const std::string& isoCode,
		tb::models::dto::APICallback<tb::models::dto::GetCurrencyResponse> callback
	);

	void GetAny(
		const tb::models::dto::APIQueryParams& params,
		tb::models::dto::PaginatedAPICallback<tb::models::dto::GetCurrencyResponse> callback
	);

}; // cl CurrencyClient

} // ns tb::api

#endif