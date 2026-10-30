#ifndef TB_API_AUTH_CLIENT_HPP
#define TB_API_AUTH_CLIENT_HPP

#include <tb/api/Client.hpp>
#include <tb/models/dto/Common.hpp>
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

	void SignIn(
		const tb::models::dto::SignInRequest& data,
		tb::models::dto::APICallback<tb::models::dto::SignInResponse> callback
	);

	void SignUp(
		const tb::models::dto::SignUpRequest& data,
		tb::models::dto::APICallback<tb::models::dto::SignUpResponse> callback
	);

};

} // ns tb::api

#endif