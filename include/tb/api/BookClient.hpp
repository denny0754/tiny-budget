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

	void CreateBook(
		const tb::models::dto::NewBookRequest& data,
		tb::models::dto::APICallback<tb::models::dto::NewBookResponse> callback
	);

}; // cl BookClient

} // ns tb::api

#endif