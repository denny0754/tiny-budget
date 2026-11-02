#ifndef TB_EVENTS_UI_PUSH_GLOBAL_COMPONENT_EVENT_HPP
#define TB_EVENTS_UI_PUSH_GLOBAL_COMPONENT_EVENT_HPP

#include <tb/events/Event.hpp>
#include <tb/ui/interfaces/Component.hpp>

#include <functional>
#include <memory>

namespace tb::events
{

class PushGlobalComponentEvent : public tb::events::UserInterfaceEvent
{
public:
	using ComponentFactory = std::function<std::unique_ptr<tb::ui::GlobalComponent>(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session,
		std::unique_ptr<tb::ui::ComponentData> data
	)>;

	explicit PushGlobalComponentEvent(ComponentFactory factory, std::unique_ptr<tb::ui::ComponentData> data = nullptr)
		: m_factory(std::move(factory)), m_data(std::move(data))
	{

	}

	std::unique_ptr<tb::ui::GlobalComponent> CreateComponent(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session) const
	{
		return m_factory ? m_factory(dispatcher, session, std::move(m_data)) : nullptr;
	}

	const char* GetName() override { return "PushGlobalComponentEvent"; }

private:
	ComponentFactory m_factory;

	mutable std::unique_ptr<tb::ui::ComponentData> m_data;
};

} // ns tb::events

#endif