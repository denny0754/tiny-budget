#ifndef TB_UI_CONTROLLER_HPP
#define TB_UI_CONTROLLER_HPP

#include <tb/events/EventDispatcher.hpp>
#include <tb/core/Session.hpp>
#include <tb/events/ui/PushGlobalComponentEvent.hpp>
#include <tb/events/ui/PushLocalComponentEvent.hpp>
#include <tb/ui/interfaces/Component.hpp>

#include <memory>

namespace tb::ui
{

class Controller
{
public:
	Controller(
		std::shared_ptr<tb::events::EventDispatcher> dispatcher,
		std::shared_ptr<tb::core::Session> session
	);

	void Render();

	void Update();

	void Shutdown();

private:

	void OnLocalComponentPush(const tb::events::PushLocalComponentEvent& event);

	void OnGlobalComponentPush(const tb::events::PushGlobalComponentEvent& event);

	class ComponentStorage
	{
	public:
		ComponentStorage() = default;
		void OnRender();
		void OnUpdate(double deltaTime = .0f);
		void OnShutdown();
		void FlushDeferred();
		void PushComponent(std::unique_ptr<tb::ui::Component> component);
	private:
		std::vector<std::unique_ptr<tb::ui::Component>> m_activeCmp;
		std::vector<std::unique_ptr<tb::ui::Component>> m_deferredCmp;
	};

	ComponentStorage m_localCmpStg;
	ComponentStorage m_globalCmpStg;

	std::shared_ptr<tb::events::EventDispatcher> m_eventDispatcher;

	std::shared_ptr<tb::core::Session> m_session;
}; // cl Controller

} // ns tb::ui

#endif