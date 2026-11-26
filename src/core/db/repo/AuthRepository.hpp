#ifndef TB_CORE_DB_REPO_HPP
#define TB_CORE_DB_REPO_HPP

#include "core/models/dto/Auth.hpp"
#include "core/models/dto/Identity.hpp"

namespace Wt::Dbo { class Session; };

namespace tb::core::db::repo
{

class AuthRepository
{
public:

	explicit AuthRepository(Wt::Dbo::Session& session);

	tb::dto::DataResult<tb::dto::Identity> SignUp(const tb::dto::SignUpCommand& data);

	tb::dto::DataResult<tb::dto::Identity> SignIn(const tb::dto::SignInCommand& data);

private:
	Wt::Dbo::Session m_session;

}; // cl AuthRepository

} // ns tb::core::db::repo

#endif