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
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session
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


class GlobalComponent : public tb::ui::Component
{
public:
	GlobalComponent(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session
	)
		: tb::ui::Component(dispatcher, session)
	{

	}
}; // cl GlobalComponent

class LocalComponent : public tb::ui::Component
{
public:
	LocalComponent(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session
	)
		: tb::ui::Component(dispatcher, session)
	{

	}

}; // cl LocalComponent

} // ns tb::ui

#endif