#include "SecuritySession.hpp"

#include "core/models/dbo/Security.hpp"

namespace tb::db
{
void SecuritySession::MapClasses()
{
	Session()->mapClass<tb::dbo::Identity>("identity");
	Session()->mapClass<tb::dbo::PasswordCredential>("password_credential");
}

int SecuritySession::ApplyMigrations(int currentVersion)
{
	return currentVersion;
}

} // ns tb::db