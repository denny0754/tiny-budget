#ifndef TB_APP_EVENTS_PUSH_UI_COMPONENT_EVENT_HPP
#define TB_APP_EVENTS_PUSH_UI_COMPONENT_EVENT_HPP

#include <memory>
#include <functional>

#include <tb/app/events/BaseUserEvent.hpp>
#include <tb/app/ui/UIComponent.hpp>

namespace tb::app::events
{

struct PushUIComponentEvent : public BaseUserEvent
{
public:
	using ComponentFactory = std::function<std::unique_ptr<ui::UIComponent>(void)>;

	explicit PushUIComponentEvent(ComponentFactory factory)
		: m_compFactory(factory)
	{

	}

	std::unique_ptr<ui::UIComponent> CreateComponent() const
	{
		return m_compFactory ? m_compFactory() : nullptr;
	}

	const char* GetName() const
	{
		return "PushUIComponentEvent";
	}
private:
	ComponentFactory m_compFactory;
}; // cl PushUIComponentEvent

} // tb::app::events

#endif