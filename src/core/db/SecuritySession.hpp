#ifndef TB_CORE_DB_SECURITY_SESSION_HPP
#define TB_CORE_DB_SECURITY_SESSION_HPP

#include "GenericSession.hpp"

namespace tb::db
{

class SecuritySession : public tb::db::GenericSession
{
public:
	SecuritySession() = default;

	SecuritySession(const SecuritySession&) = delete;
	SecuritySession& operator=(const SecuritySession&) = delete;
	SecuritySession(SecuritySession&&) = delete;
	SecuritySession& operator=(SecuritySession&&) = delete;

protected:
	void MapClasses() override;

	[[nodiscard]] int ApplyMigrations(int currentVersion) override;

}; // cl SecuritySession

} // ns tb::db

#endif