#ifndef TB_CORE_APP_APPLICATION_HPP
#define TB_CORE_APP_APPLICATION_HPP

#include "core/db/DatabaseWorker.hpp"
#include "ui/stores/SystemStore.hpp"
#include "ui/stores/UserStore.hpp"
#include "ui/ViewManager.hpp"

#include <memory>

namespace tb::core
{

class Application
{
public:
	Application();

	void Run();

	~Application();

private:
	tb::ui::SystemStore m_sysStore;
	tb::ui::UserStore m_usrStore;

	tb::db::DatabaseWorker m_dbWorker;

	tb::ui::ViewManager m_viewManager;

}; // cl Application

} // ns tb::core

#endif