/*
==========================================================================
 CHANGE LOG
==========================================================================
 Date       | Author        | Task ID | Description
------------+---------------+---------+-----------------------------------
 2026-11-19 | Diego Vaccher | TB-8    | Implementaton of Security Session
==========================================================================
*/

#ifndef TB_CORE_DB_SECURITY_SESSION_HPP
#define TB_CORE_DB_SECURITY_SESSION_HPP

#include "GenericSession.hpp"

namespace tb::core::db
{

class SecuritySession : public tb::core::db::GenericSession
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

} // ns tb::core::db

#endif