#include <tb/app/ui/Controller.hpp>
#include <tb/tools/Logging.hpp>

namespace tb::app::ui
{

Controller::Controller(std::shared_ptr<tb::app::SessionContext> sessionCtx)
{
	m_sessionContext = sessionCtx;
}

void Controller::Init()
{
	tb::tools::log::GetCoreLogger()->info("UI Controller is being initialized.");

	m_sessionContext->eventDispatcher->Subscribe<tb::app::events::PushGlobalComponentEvent>(
		TB_APP_BIND_EVENT_FN(OnPushGlobalComponent)
	);
	
	m_sessionContext->eventDispatcher->Subscribe<tb::app::events::PushLocalComponentEvent>(
		TB_APP_BIND_EVENT_FN(OnPushLocalComponent)
	);
}

void Controller::Update(double deltaTime)
{
	m_globalCmpStg.OnUpdate(deltaTime);
	m_localCmpStg.OnUpdate(deltaTime);

	// Flushing Deferred components to the Active queue.
	m_globalCmpStg.FlushDeferred();
	m_localCmpStg.FlushDeferred();
}

void Controller::Render()
{
	m_globalCmpStg.OnRender();
	m_localCmpStg.OnRender();
}

void Controller::Shutdown()
{
	m_globalCmpStg.OnShutdown();
	m_localCmpStg.OnShutdown();
}

void Controller::OnPushLocalComponent(const tb::app::events::PushLocalComponentEvent& event)
{
	auto cmp = event.CreateComponent();
	if (cmp)
	{
		cmp->BindSessionContext(m_sessionContext);
		//TODO: Define method and member for WorkspaceContext.
		//cmp->BindWorkspaceContext(m_workspaceContext);
		cmp->OnInit();
		m_globalCmpStg.PushComponent(std::move(cmp));
	}
	event.Handled = true;
}

void Controller::OnPushGlobalComponent(const tb::app::events::PushGlobalComponentEvent& event)
{
	auto cmp = event.CreateComponent();
	if (cmp)
	{
		cmp->BindSessionContext(m_sessionContext);
		cmp->OnInit();
		m_globalCmpStg.PushComponent(std::move(cmp));
	}
	event.Handled = true;
}

void Controller::ComponentStorage::OnRender()
{
	for (auto& cmp : m_activeCmp)
	{
		cmp->OnRender();
	}
}

void Controller::ComponentStorage::OnUpdate(double deltaTime)
{
	for (auto& cmp : m_activeCmp)
	{
		cmp->OnUpdate(deltaTime);
	}
}

void Controller::ComponentStorage::OnShutdown()
{
	for (auto& cmp : m_activeCmp)
	{
		cmp->OnShutdown();
	}
}

void Controller::ComponentStorage::FlushDeferred()
{
	for (auto& cmp : m_deferredCmp)
	{
		m_activeCmp.push_back(std::move(cmp));
	}
	m_deferredCmp.clear();

	std::erase_if(
		m_activeCmp,
		[](const std::unique_ptr<tb::app::ui::IComponent>& cmp) {
			if (cmp->ShouldClose())
			{
				cmp->OnShutdown();
				return true;
			}
			return false;
		}
	);
}

void Controller::ComponentStorage::PushComponent(std::unique_ptr<IComponent> component)
{
	m_deferredCmp.push_back(std::move(component));
}


} // ns tb::app::ui