#include "UserSession.hpp"

#include "../models/dbo/User.hpp"

namespace tb::core::db
{
void UserSession::MapClasses()
{
	Session()->mapClass<tb::models::dbo::Book>("book");
	Session()->mapClass<tb::models::dbo::Account>("account");
	Session()->mapClass<tb::models::dbo::Partner>("partner");
	Session()->mapClass<tb::models::dbo::Transaction>("transaction");
	Session()->mapClass<tb::models::dbo::TransactionItem>("transaction_item");
	Session()->mapClass<tb::models::dbo::Product>("product");
	Session()->mapClass<tb::models::dbo::BookStatus>("book_status");
	Session()->mapClass<tb::models::dbo::BookStatusText>("book_status_text");
	Session()->mapClass<tb::models::dbo::Currency>("currency");
	Session()->mapClass<tb::models::dbo::CurrencyText>("currency_text");
	Session()->mapClass<tb::models::dbo::AccountType>("account_type");
	Session()->mapClass<tb::models::dbo::AccountTypeText>("account_type_text");
	Session()->mapClass<tb::models::dbo::Language>("language");
}

int UserSession::ApplyMigrations(int currentVersion)
{
	return currentVersion;
}

} // ns tb::core::db