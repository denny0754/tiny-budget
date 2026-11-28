#ifndef TB_UI_STORES_AUTH_STORE_HPP
#define TB_UI_STORES_AUTH_STORE_HPP

#include "ui/stores/GenericStore.hpp"
#include "core/db/DatabaseWorker.hpp"
#include "core/models/dto/Auth.hpp"

namespace tb::ui
{

class AuthStore : public tb::ui::GenericStore
{
public:
	explicit AuthStore(const tb::db::DatabaseWorker& db_worker);

	void SignUp(const tb::dto::SignUpCommand& data);

	void SignIn(const tb::dto::SignInCommand& data);

private:
	tb::db::DatabaseWorker m_dbWorker;
}; // cl SystemStore

} // ns tb::ui

#endif