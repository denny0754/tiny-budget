#ifndef TB_CORE_SESSION_HPP
#define TB_CORE_SESSION_HPP

#include <tb/events/EventDispatcher.hpp>
#include <tb/api/Service.hpp>
#include <tb/core/Context.hpp>
#include <tb/events/session/IdentitySignedInEvent.hpp>
#include <tb/events/session/IdentitySignedOutEvent.hpp>

#include <memory>

namespace tb::core
{

class Session
{
public:
	Session(std::shared_ptr<tb::events::EventDispatcher> dispatcher);

	const std::shared_ptr<tb::api::Service>& GetService() const
	{
		return m_service;
	}

private:
	std::shared_ptr<tb::events::EventDispatcher> m_eventDispatcher;

	std::shared_ptr<tb::api::Service> m_service;

	std::shared_ptr<tb::core::SessionContext> m_sessionContext;

	void OnIdentitySignedIn(const tb::events::IdentitySignedInEvent& event);

	void OnIdentitySignedOut(const tb::events::IdentitySignedOutEvent& event);

}; // cl Session

} // ns tb::core

#endif