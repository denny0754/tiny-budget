#ifndef TB_API_BOOK_CLIENT_HPP
#define TB_API_BOOK_CLIENT_HPP

#include <tb/api/Client.hpp>
#include <tb/models/dto/Common.hpp>
#include <tb/models/dto/Book.hpp>

namespace tb::api
{

class BookClient : public tb::api::Client
{
public:
	BookClient(const std::shared_ptr<tb::core::SessionContext>& ctx,
		const std::shared_ptr<Wt::Dbo::Session>& db)
		: tb::api::Client(ctx, db)
	{

	}

	void Create(
		const tb::models::dto::CreateBookRequest& data,
		tb::models::dto::APICallback<tb::models::dto::CreateBookResponse> callback
	);

	void UpdateById(
		const std::string& id,
		const tb::models::dto::UpdateBookRequest& data,
		tb::models::dto::APICallback<tb::models::dto::UpdateBookResponse> callback
	);

	void GetById(
		const std::string& id,
		tb::models::dto::APICallback<tb::models::dto::GetBookResponse> callback
	);

	void GetAny(
		const tb::models::dto::APIQueryParams& params,
		tb::models::dto::PaginatedAPICallback<tb::models::dto::GetBookResponse> callback
	);

}; // cl BookClient

} // ns tb::api

#endif