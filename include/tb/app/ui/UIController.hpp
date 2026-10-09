#ifndef TB_APP_UI_UI_CONTROLLER_HPP
#define TB_APP_UI_UI_CONTROLLER_HPP

#include <vector>
#include <memory>

#include <tb/app/SessionContext.hpp>
#include <tb/app/ui/UIComponent.hpp>
#include <tb/app/events/PushUIComponentEvent.hpp>

namespace tb::app::ui
{

class UIController
{
public:
	UIController(std::shared_ptr<SessionContext> sessionCtx)
		: m_sessionCtx(sessionCtx)
	{

	}

	void Init();

	void Update(double deltaTime = .0f);

	void Render();

	void Shutdown();

private:
	void OnPushComponent(const events::PushUIComponentEvent& event);

private:
	std::shared_ptr<SessionContext> m_sessionCtx;

	std::vector<std::unique_ptr<UIComponent>> m_activeComps;
	std::vector<std::unique_ptr<UIComponent>> m_deferredComps;


}; // cl UIController

} // ns tb::app::ui

#endif