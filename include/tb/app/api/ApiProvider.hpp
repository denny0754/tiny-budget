#ifndef TB_APP_MODS_API_PROVIDER_HPP
#define TB_APP_MODS_API_PROVIDER_HPP

#include <tb/core/mod/Module.hpp>

#include <tb/app/models/api/Identity.hpp>

namespace tb::app::api
{

template<typename T>
struct APIResult
{
	std::string ErrorMessage;
	bool Success;
	T Result;
};

template<typename T>
using APICallback = std::function<void(const APIResult<T>&)>;

class ApiProvider
{
public:
	virtual void Init() = 0;

	virtual void SignUp(
		const tb::app::models::api::SignUpRequest& data,
		APICallback<tb::app::models::api::SignUpResponse> callback
	) = 0;

	virtual void SignIn(
		const tb::app::models::api::SignInRequest& data,
		APICallback<tb::app::models::api::SignInResponse> callback
	)= 0;
};

} // ns tb::app::mods
#endif