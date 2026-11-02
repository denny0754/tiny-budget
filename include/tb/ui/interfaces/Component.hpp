#ifndef TB_UI_INTERFACES_COMPONENT_HPP
#define TB_UI_INTERFACES_COMPONENT_HPP

#include <tb/events/EventDispatcher.hpp>
#include <tb/core/Session.hpp>

namespace tb::ui
{

struct ComponentData
{
public:
	~ComponentData() = default;

}; // st ComponentData

class Component
{
public:
	Component(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session,
		std::unique_ptr<tb::ui::ComponentData> data
	)
		: m_eventDispatcher(dispatcher), m_session(session), m_data(std::move(data))
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

	const std::unique_ptr<tb::ui::ComponentData>& GetData()
	{
		return m_data;
	}

	void Close()
	{
		m_isClosed = true;
	}

private:
	std::shared_ptr<tb::events::EventDispatcher> m_eventDispatcher;

	std::shared_ptr<tb::core::Session> m_session;

	std::unique_ptr<tb::ui::ComponentData> m_data;

	bool m_isClosed{ false };
}; // cl Component


class GlobalComponent : public tb::ui::Component
{
public:
	GlobalComponent(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session,
		std::unique_ptr<tb::ui::ComponentData> data
	)
		: tb::ui::Component(dispatcher, session, std::move(data))
	{

	}
}; // cl GlobalComponent

class LocalComponent : public tb::ui::Component
{
public:
	LocalComponent(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session,
		std::unique_ptr<tb::ui::ComponentData> data
	)
		: tb::ui::Component(dispatcher, session, std::move(data))
	{

	}

}; // cl LocalComponent

} // ns tb::ui

#endif