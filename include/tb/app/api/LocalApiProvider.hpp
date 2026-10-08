#ifndef TB_APP_API_LOCAL_API_PROVIDER_HPP
#define TB_APP_API_LOCAL_API_PROVIDER_HPP

#include <Wt/Dbo/Session.h>

#include <tb/app/api/APIProvider.hpp>


namespace tb::app::api
{

class LocalApiProvider : public tb::app::api::ApiProvider
{
public:
	void Init() override;

	void SignUp(
		const tb::app::models::SignUpRequest& data,
		APICallback<tb::app::models::SignUpResponse> callback
	) override;

	void SignIn(
		const tb::app::models::SignInRequest& data,
		APICallback<tb::app::models::SignInResponse> callback
	);

private:
	Wt::Dbo::Session m_dbSession;
};

}

#endif