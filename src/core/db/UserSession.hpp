#ifndef TB_CORE_DB_USER_SESSION_HPP
#define TB_CORE_DB_USER_SESSION_HPP

#include "GenericSession.hpp"

namespace tb::db
{

class UserSession : public tb::db::GenericSession
{
public:
	UserSession() = default;

	UserSession(const UserSession&) = delete;
	UserSession& operator=(const UserSession&) = delete;
	UserSession(UserSession&&) = delete;
	UserSession& operator=(UserSession&&) = delete;

protected:
	void MapClasses() override;

	[[nodiscard]] int ApplyMigrations(int currentVersion) override;

}; // cl UserSession

} // ns tb::db

#endif