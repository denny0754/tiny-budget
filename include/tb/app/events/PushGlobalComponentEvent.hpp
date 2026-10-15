#ifndef TB_APP_EVENTS_PUSH_GLOBAL_COMPONENT_EVENT_HPP
#define TB_APP_EVENTS_PUSH_GLOBAL_COMPONENT_EVENT_HPP

#include <memory>
#include <functional>

#include <tb/app/events/BaseUserEvent.hpp>
#include <tb/app/ui/GlobalComponent.hpp>

namespace tb::app::events
{

struct PushGlobalComponentEvent : public BaseUserEvent
{
public:
	using ComponentFactory = std::function<std::unique_ptr<tb::app::ui::GlobalComponent>(void)>;

	explicit PushGlobalComponentEvent(ComponentFactory factory)
		: m_compFactory(factory)
	{

	}

	std::unique_ptr<tb::app::ui::GlobalComponent> CreateComponent() const
	{
		return m_compFactory ? m_compFactory() : nullptr;
	}

	const char* GetName() const
	{
		return "PushGlobalComponentEvent";
	}
private:
	ComponentFactory m_compFactory;
}; // cl PushGlobalComponentEvent

} // tb::app::events

#endif