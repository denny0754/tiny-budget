#ifndef TB_UI_INTERFACES_COMPONENT_HPP
#define TB_UI_INTERFACES_COMPONENT_HPP

#include <tb/events/EventDispatcher.hpp>
#include <tb/ui/Common.hpp>
#include <tb/core/Session.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

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
		static thread_local boost::uuids::random_generator gen;
		m_id = boost::uuids::to_string(gen());
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

	virtual const std::string& GetComponentId()
	{
		return m_id;
	}

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

	template<typename T>
	const T* GetDataAs()
	{
		static_assert(std::is_base_of_v<tb::ui::ComponentData, T>, "T must derive from tb::ui::ComponentData");
		return static_cast<T*>(m_data.get());
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

	std::string m_id;
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