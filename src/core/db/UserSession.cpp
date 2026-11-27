#include "UserSession.hpp"

#include "core/models/dbo/User.hpp"

namespace tb::db
{
void UserSession::MapClasses()
{
	Session()->mapClass<tb::dbo::Book>("book");
	Session()->mapClass<tb::dbo::Account>("account");
	Session()->mapClass<tb::dbo::Partner>("partner");
	Session()->mapClass<tb::dbo::Transaction>("transaction");
	Session()->mapClass<tb::dbo::TransactionItem>("transaction_item");
	Session()->mapClass<tb::dbo::Product>("product");
	Session()->mapClass<tb::dbo::BookStatus>("book_status");
	Session()->mapClass<tb::dbo::BookStatusText>("book_status_text");
	Session()->mapClass<tb::dbo::Currency>("currency");
	Session()->mapClass<tb::dbo::CurrencyText>("currency_text");
	Session()->mapClass<tb::dbo::AccountType>("account_type");
	Session()->mapClass<tb::dbo::AccountTypeText>("account_type_text");
	Session()->mapClass<tb::dbo::Language>("language");
}

int UserSession::ApplyMigrations(int currentVersion)
{
	return currentVersion;
}

} // ns tb::db