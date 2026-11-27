#ifndef TB_CORE_DB_REPO_AUTH_REPOSITORY_HPP
#define TB_CORE_DB_REPO_AUTH_REPOSITORY_HPP

#include "core/db/repo/Repository.hpp"
#include "core/models/dto/Auth.hpp"
#include "core/models/dto/Identity.hpp"

namespace tb::db
{

class AuthRepository : public tb::db::Repository
{
public:

	explicit AuthRepository(const std::shared_ptr<Wt::Dbo::Session>& session);

	tb::dto::DataResult<tb::dto::Identity> SignUp(const tb::dto::SignUpCommand& data);

	tb::dto::DataResult<tb::dto::Identity> SignIn(const tb::dto::SignInCommand& data);

protected:

	std::string HashPassword(const std::string& password) const;

	bool VerifyPasswordHash(const std::string& password, const std::string& hash) const;
}; // cl AuthRepository

} // ns tb::db

#endif