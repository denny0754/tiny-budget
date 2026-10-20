#ifndef TB_APP_API_IAUTH_CLIENT_HPP
#define TB_APP_API_IAUTH_CLIENT_HPP

#include <tb/models/dto/Auth.hpp>
#include <tb/models/dto/Common.hpp>
#include <tb/app/api/BaseClient.hpp>

namespace tb::app::api
{

class IAuthClient : public BaseClient
{
public:
	virtual ~IAuthClient() = default;

	virtual void SignUp(
		const tb::models::dto::SignUpRequest& data,
		tb::models::dto::APICallback<tb::models::dto::SignUpResponse>
	) = 0;

	virtual void SignIn(
		const tb::models::dto::SignInRequest& data,
		tb::models::dto::APICallback<tb::models::dto::SignInResponse>
	) = 0;

}; // cl IAuthClient

} // ns tb::app::api

#endif