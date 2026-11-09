/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#ifndef TB_API_AUTH_CLIENT_HPP
#define TB_API_AUTH_CLIENT_HPP

#include <tb/api/Client.hpp>
#include <tb/models/dto/Auth.hpp>

namespace tb::api
{

class AuthClient : public tb::api::Client
{
public:
	AuthClient(const std::shared_ptr<tb::core::SessionContext>& ctx,
		const std::shared_ptr<Wt::Dbo::Session>& db)
		: tb::api::Client(ctx, db)
	{

	}

	tb::models::dto::SignInResponse SignIn(
		const tb::models::dto::SignInRequest& data
	);

	tb::models::dto::SignUpResponse SignUp(
		const tb::models::dto::SignUpRequest& data
	);

};

} // ns tb::api

#endif