#include "SecuritySession.hpp"

#include "core/models/dbo/Security.hpp"

namespace tb::core::db
{
void SecuritySession::MapClasses()
{
	Session()->mapClass<tb::models::dbo::Identity>("identity");
	Session()->mapClass<tb::models::dbo::PasswordCredential>("password_credential");
}

int SecuritySession::ApplyMigrations(int currentVersion)
{
	return currentVersion;
}

} // ns tb::core::db