/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#ifndef TB_API_CLIENT_HPP
#define TB_API_CLIENT_HPP

#include <tb/core/Context.hpp>

#include <memory>

namespace Wt::Dbo { class Session; }

namespace tb::api
{

class Client
{
public:
	Client(const std::shared_ptr<tb::core::SessionContext>& ctx, const std::shared_ptr<Wt::Dbo::Session>& db)
		: m_sessionContext(ctx), m_dbSession(db)
	{

	}

	virtual ~Client() = default;

protected:
	const std::shared_ptr<tb::core::SessionContext>& GetSessionCtx() const
	{
		return m_sessionContext;
	}

	const std::shared_ptr<Wt::Dbo::Session>& GetDbSession() const
	{
		return m_dbSession;
	}

private:
	std::shared_ptr<tb::core::SessionContext> m_sessionContext;

	std::shared_ptr<Wt::Dbo::Session> m_dbSession;
}; // cl Client

} // ns tb::api

#endif