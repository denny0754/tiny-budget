#ifndef TB_EVENTS_UI_PUSH_LOCAL_COMPONENT_EVENT_HPP
#define TB_EVENTS_UI_PUSH_LOCAL_COMPONENT_EVENT_HPP

#include <tb/events/Event.hpp>
#include <tb/ui/interfaces/Component.hpp>

#include <functional>
#include <memory>

namespace tb::events
{

class PushLocalComponentEvent: public tb::events::UserInterfaceEvent
{
public:
	using ComponentFactory = std::function<std::unique_ptr<tb::ui::LocalComponent>(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session
	)>;

	explicit PushLocalComponentEvent(ComponentFactory factory)
		: m_factory(factory)
	{

	}

	std::unique_ptr<tb::ui::LocalComponent> CreateComponent(
		const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
		const std::shared_ptr<tb::core::Session>& session) const
	{
		return m_factory ? m_factory(dispatcher, session) : nullptr;
	}

	const char* GetName() override { return "PushLocalComponentEvent"; }

private:
	ComponentFactory m_factory;
};

} // ns tb::events

#endif