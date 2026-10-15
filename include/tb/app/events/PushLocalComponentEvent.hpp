#ifndef TB_APP_EVENTS_PUSH_LOCAL_COMPONENT_EVENT_HPP
#define TB_APP_EVENTS_PUSH_LOCAL_COMPONENT_EVENT_HPP

#include <memory>
#include <functional>

#include <tb/app/events/BaseUserEvent.hpp>
#include <tb/app/ui/LocalComponent.hpp>

namespace tb::app::events
{

struct PushLocalComponentEvent : public BaseUserEvent
{
public:
	using ComponentFactory = std::function<std::unique_ptr<tb::app::ui::LocalComponent>(void)>;

	explicit PushLocalComponentEvent(ComponentFactory factory)
		: m_compFactory(factory)
	{

	}

	std::unique_ptr<tb::app::ui::LocalComponent> CreateComponent() const
	{
		return m_compFactory ? m_compFactory() : nullptr;
	}

	const char* GetName() const
	{
		return "PushLocalComponentEvent";
	}
private:
	ComponentFactory m_compFactory;
}; // cl PushLocalComponentEvent

} // tb::app::events

#endif