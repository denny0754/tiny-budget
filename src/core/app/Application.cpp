#include "core/app/Application.hpp"

namespace tb::core
{

Application::Application()
{
	m_dbWorker = tb::db::DatabaseWorker();
	m_dbWorker.InitializeSecuritySession("./data/security.db");
	m_dbWorker.Start();

	m_sysStore = tb::ui::SystemStore(m_dbWorker);
	m_usrStore = tb::ui::UserStore(m_dbWorker);

	m_viewManager = tb::ui::ViewManager(m_sysStore, m_usrStore);

}

void Application::Run()
{
	while (!m_viewManager.ShouldClose())
	{
		m_viewManager.PollEvents();

		m_sysStore.Poll();
		m_usrStore.Poll();

		m_viewManager.Update();
		m_viewManager.Render();
	}
}

} // ns tb::core