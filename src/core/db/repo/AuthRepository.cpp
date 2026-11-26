#include "core/db/repo/AuthRepository.hpp"

namespace tb::core::db
{

AuthRepository::AuthRepository(Wt::Dbo::Session& session)
	: m_session(session)
{

}

tb::dto::DataResult<tb::dto::Identity> AuthRepository::SignUp(const tb::dto::SignUpCommand& data)
{
	//TODO: Implement
	return {};
}

tb::dto::DataResult<tb::dto::Identity> AuthRepository::SignIn(const tb::dto::SignInCommand& data)
{
	//TODO: Implement
	return {};
}

} // ns tb::core::db::