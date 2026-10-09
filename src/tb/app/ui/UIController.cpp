#include <tb/app/ui/UIController.hpp>

namespace tb::app::ui
{

void UIController::Init()
{
	m_sessionCtx->eventDispatcher->Subscribe<events::PushUIComponentEvent>(TB_APP_BIND_EVENT_FN(OnPushComponent));
}

void UIController::Render()
{
	for (auto& comp : m_activeComps)
	{
		comp->OnRender();
	}
}

void UIController::Update(double deltaTime)
{
	for (auto& comp : m_activeComps)
	{
		comp->OnUpdate(deltaTime);
	}
	// Move all deferred objects to the active queue

	for (auto& deferredComp : m_deferredComps)
	{
		m_activeComps.push_back(std::move(deferredComp));
	}
	m_deferredComps.clear();
}

void UIController::Shutdown()
{

}

void UIController::OnPushComponent(const events::PushUIComponentEvent& event)
{
	// Move object to the deferred queue
	auto comp = event.CreateComponent();
	if (comp)
	{
		comp->BindSessionContext(m_sessionCtx);
		comp->OnInit();
		m_deferredComps.push_back(std::move(comp));
	}
}

} // ns tb::app::ui