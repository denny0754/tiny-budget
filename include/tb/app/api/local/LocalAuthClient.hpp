#ifndef TB_APP_API_LOCAL_LOCAL_AUTH_CLIENT
#define TB_APP_API_LOCAL_LOCAL_AUTH_CLIENT

#include <tb/models/dto/Auth.hpp>
#include <tb/app/api/IAuthClient.hpp>

#include <memory>

namespace Wt::Dbo { class Session; }

namespace tb::app::api
{
class LocalApiService;

class LocalAuthClient : public tb::app::api::IAuthClient
{
public:
	LocalAuthClient(std::shared_ptr<Wt::Dbo::Session> session) { m_dbSession = session; }

	void SignUp(
		const tb::models::dto::SignUpRequest& data,
		tb::models::dto::APICallback<tb::models::dto::SignUpResponse>
	) override;

	void SignIn(
		const tb::models::dto::SignInRequest& data,
		tb::models::dto::APICallback<tb::models::dto::SignInResponse>
	) override;

private:
	std::shared_ptr<Wt::Dbo::Session> m_dbSession;
}; // cl LocalApiClient

} // ns tb::app::api

#endif