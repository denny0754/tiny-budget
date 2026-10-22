#ifndef TB_UI_INTERFACES_COMPONENT_HPP
#define TB_UI_INTERFACES_COMPONENT_HPP

#include <tb/events/EventDispatcher.hpp>
#include <tb/core/Session.hpp>

namespace tb::ui
{

class Component
{
public:
	Component(
		std::shared_ptr<tb::events::EventDispatcher> dispatcher,
		std::shared_ptr<tb::core::Session> session
	)
		: m_eventDispatcher(dispatcher), m_session(session)
	{

	}

	virtual ~Component() = default;

	virtual void OnInit() = 0;

	virtual void OnUpdate() = 0;

	virtual void OnRender() = 0;

	virtual void OnShutdown() = 0;

	const bool ShouldClose() const
	{
		return m_isClosed;
	}

	virtual const char* GetComponentId() const = 0;

protected:

	const std::shared_ptr<tb::events::EventDispatcher>& GetEventDispatcher() const
	{
		return m_eventDispatcher;
	}

	const std::shared_ptr<tb::core::Session>& GetSession() const
	{
		return m_session;
	}

	void Close()
	{
		m_isClosed = true;
	}

private:
	std::shared_ptr<tb::events::EventDispatcher> m_eventDispatcher;

	std::shared_ptr<tb::core::Session> m_session;

	bool m_isClosed{ false };
}; // cl Component

} // ns tb::ui

#endif