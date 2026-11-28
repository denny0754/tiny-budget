#ifndef TB_UI_STORES_SYSTEM_STORE_HPP
#define TB_UI_STORES_SYSTEM_STORE_HPP

#include "ui/stores/GenericStore.hpp"
#include "core/db/DatabaseWorker.hpp"

namespace tb::ui
{

class SystemStore : public tb::ui::GenericStore
{
public:
	explicit SystemStore(const tb::db::DatabaseWorker& db_worker);

private:
	tb::db::DatabaseWorker m_dbWorker;
}; // cl SystemStore

} // ns tb::ui

#endif