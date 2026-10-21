#ifndef TB_API_LOCAL_LOCAL_AUTH_CLIENT
#define TB_API_LOCAL_LOCAL_AUTH_CLIENT

#include <tb/models/dto/Auth.hpp>
#include <tb/api/interfaces/IAuthClient.hpp>
#include <tb/api/local/LocalBaseClient.hpp>

#include <memory>

namespace Wt::Dbo { class Session; }

namespace tb::api
{

class LocalAuthClient : public tb::api::IAuthClient, public tb::api::LocalBaseClient
{
public:
	explicit LocalAuthClient(std::shared_ptr<tb::api::SessionContext> ctx, std::shared_ptr<Wt::Dbo::Session> db)
		: LocalBaseClient(ctx, db) { }

	void SignUp(
		const tb::models::dto::SignUpRequest& data,
		tb::models::dto::APICallback<tb::models::dto::SignUpResponse>
	) override;

	void SignIn(
		const tb::models::dto::SignInRequest& data,
		tb::models::dto::APICallback<tb::models::dto::SignInResponse>
	) override;

}; // cl LocalApiClient

} // ns tb::app::api

#endif