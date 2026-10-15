#ifndef TB_APP_UI_CONTROLLER_HPP
#define TB_APP_UI_CONTROLLER_HPP

#include <tb/app/SessionContext.hpp>
#include <tb/app/ui/IComponent.hpp>
#include <tb/app/ui/GlobalComponent.hpp>
#include <tb/app/ui/LocalComponent.hpp>
#include <tb/app/events/PushGlobalComponentEvent.hpp>
#include <tb/app/events/PushLocalComponentEvent.hpp>

namespace tb::app::ui
{

class Controller
{
public:
	Controller(std::shared_ptr<tb::app::SessionContext> sessionCtx);

	void Init();

	void Update(double deltaTime = .0f);

	void Render();

	void Shutdown();

private:
	void OnPushLocalComponent(const tb::app::events::PushLocalComponentEvent& event);
	void OnPushGlobalComponent(const tb::app::events::PushGlobalComponentEvent& event);

	class ComponentStorage
	{
	public:
		ComponentStorage() = default;
		void OnRender();
		void OnUpdate(double deltaTime = .0f);
		void OnShutdown();
		void FlushDeferred();
		void PushComponent(std::unique_ptr<IComponent> component);
	private:
		std::vector<std::unique_ptr<IComponent>> m_activeCmp;
		std::vector<std::unique_ptr<IComponent>> m_deferredCmp;
	};
	 
	ComponentStorage m_localCmpStg;
	ComponentStorage m_globalCmpStg;
	std::shared_ptr<tb::app::SessionContext> m_sessionContext;
}; // cl Controller

} // ns tb::app::ui

#endif