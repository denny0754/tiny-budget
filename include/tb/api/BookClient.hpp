/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#ifndef TB_API_BOOK_CLIENT_HPP
#define TB_API_BOOK_CLIENT_HPP

#include <tb/api/Client.hpp>
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

	tb::models::dto::CreateBookResponse Create(
		const tb::models::dto::CreateBookRequest& data
	);

	tb::models::dto::UpdateBookResponse UpdateById(
		const std::string& id,
		const tb::models::dto::UpdateBookRequest& data
	);

	tb::models::dto::GetBookResponse GetById(
		const std::string& id
	);

	tb::models::dto::GetBookResponse GetAny(
		//TODO: Add query parameters
	);

}; // cl BookClient

} // ns tb::api

#endif