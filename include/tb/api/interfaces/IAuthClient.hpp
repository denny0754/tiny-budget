#ifndef TB_API_INTERFACES_IAUTH_CLIENT_HPP
#define TB_API_INTERFACES_IAUTH_CLIENT_HPP

#include <tb/models/dto/Auth.hpp>
#include <tb/models/dto/Common.hpp>

namespace tb::api
{

class IAuthClient
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

} // ns tb::api

#endif