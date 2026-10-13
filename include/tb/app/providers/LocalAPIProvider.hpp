#ifndef TB_APP_PROVIDERS_LOCAL_API_PROVIDER_HPP
#define TB_APP_PROVIDERS_LOCAL_API_PROVIDER_HPP

#include <memory>

#include <tb/app/providers/APIProvider.hpp>

namespace Wt::Dbo { class Session; }

namespace tb::app::providers
{

class LocalAPIProvider : public APIProvider
{
public:
	LocalAPIProvider();

	void SignUp(
		const tb::models::dto::SignUpRequest& data,
		APIProvider::APICallback<tb::models::dto::SignUpResponse> callback
	) override;

	void SignIn(
		const tb::models::dto::SignInRequest& data,
		APIProvider::APICallback<tb::models::dto::SignInResponse> callback
	);

private:
	std::unique_ptr<Wt::Dbo::Session> m_dbSession;

}; // cl LocalAPIProvider

} // ns tb::app::providers

#endif