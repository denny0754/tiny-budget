#ifndef TB_API_LOCAL_LOCAL_FINANCIAL_BOOK_CLIENT_HPP
#define TB_API_LOCAL_LOCAL_FINANCIAL_BOOK_CLIENT_HPP

#include <tb/models/dto/FinancialBook.hpp>
#include <tb/api/interfaces/IFinancialBookClient.hpp>
#include <tb/api/local/LocalBaseClient.hpp>

#include <memory>

namespace Wt::Dbo { class Session; }

namespace tb::api
{

class LocalFinancialBookClient : public tb::api::IFinancialBookClient, public tb::api::LocalBaseClient
{
public:
	explicit LocalFinancialBookClient(std::shared_ptr<tb::api::SessionContext> ctx, std::shared_ptr<Wt::Dbo::Session> db)
		: LocalBaseClient(ctx, db)
	{

	}

	void CreateFinancialBook(
		const tb::models::dto::CreateFinancialBookRequest& data,
		tb::models::dto::APICallback<tb::models::dto::CreateFinancialBookResponse> callback
	) override;

	void GetFinancialBookById(
		const std::string& id,
		tb::models::dto::APICallback<tb::models::dto::GetFinancialBookResponse> callback
	) override;

	void GetFinancialBooks(
		const tb::models::dto::APIQueryParams& params,
		tb::models::dto::PaginatedAPICallback<tb::models::dto::GetFinancialBookResponse> callback
	) override;

}; // cl LocalApiClient

} // ns tb::app::api

#endif