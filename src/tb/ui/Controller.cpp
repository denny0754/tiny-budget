#include <tb/ui/Controller.hpp>

namespace tb::ui
{

Controller::Controller(
	std::shared_ptr<tb::events::EventDispatcher> dispatcher,
	std::shared_ptr<tb::core::Session> session
)
	: m_eventDispatcher(dispatcher), m_session(session)
{
	m_eventDispatcher->Subscribe<tb::events::PushGlobalComponentEvent>(
		TB_BIND_EVENT_FN(OnGlobalComponentPush)
	);

	m_eventDispatcher->Subscribe<tb::events::PushLocalComponentEvent>(
		TB_BIND_EVENT_FN(OnLocalComponentPush)
	);
}

void Controller::Render()
{
	m_globalCmpStg.OnRender();
	m_localCmpStg.OnRender();
}

void Controller::Update()
{
	m_globalCmpStg.OnUpdate();
	m_localCmpStg.OnUpdate();

	m_globalCmpStg.FlushDeferred();
	m_localCmpStg.FlushDeferred();
}

void Controller::Shutdown()
{
	m_globalCmpStg.OnShutdown();
	m_localCmpStg.OnShutdown();
}

void Controller::OnGlobalComponentPush(const tb::events::PushGlobalComponentEvent& event)
{
	auto cmp = event.CreateComponent(m_eventDispatcher, m_session);
	if (cmp)
	{
		cmp->OnInit();
		m_globalCmpStg.PushComponent(std::move(cmp));
	}
	event.Handled = true;
}

void Controller::OnLocalComponentPush(const tb::events::PushLocalComponentEvent& event)
{
	auto cmp = event.CreateComponent(m_eventDispatcher, m_session);
	if (cmp)
	{
		cmp->OnInit();
		m_localCmpStg.PushComponent(std::move(cmp));
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
		cmp->OnUpdate();
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
		[](const std::unique_ptr<tb::ui::Component>& cmp) {
			if (cmp->ShouldClose())
			{
				cmp->OnShutdown();
				return true;
			}
			return false;
		}
	);
}

void Controller::ComponentStorage::PushComponent(std::unique_ptr<tb::ui::Component> component)
{
	m_deferredCmp.push_back(std::move(component));
}

} // ns tb::ui