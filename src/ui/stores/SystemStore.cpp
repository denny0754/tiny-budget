#include "ui/stores/SystemStore.hpp"
#include "ui/stores/AuthStore.hpp"

namespace tb::ui
{

SystemStore::SystemStore(const tb::db::DatabaseWorker& db_worker)
{
	m_dbWorker = db_worker;
	RegisterSubStore<tb::ui::AuthStore>(m_dbWorker);
}

} // ns tb::ui