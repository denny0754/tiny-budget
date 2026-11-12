/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-10 | Diego Vaccher | UI-0000006-M  | Visualize Active Books on Side Menu
================================================================================
*/

#include <tb/models/bdo/Book.hpp>

namespace tb::models::bdo
{

Book::Book(
	const std::string& guid,
	const std::chrono::system_clock::time_point& created_on,
	const std::chrono::system_clock::time_point& updated_on,
	const std::string& identity_guid,
	const std::string& name,
	const std::string& description,
	const std::string& dflt_currency_iso_code
)
	:
	tb::models::bdo::BaseDataObject(guid, created_on, updated_on),
	m_identityGuid(identity_guid),
	m_name(name),
	m_description(description),
	m_defaultCurrencyIsoCode(dflt_currency_iso_code)
{

}

const std::string& Book::GetIdentityGuid() const
{
	return m_identityGuid;
}

const std::string& Book::GetName() const
{
	return m_name;
}

const std::string& Book::GetDescription() const
{
	return m_description;
}

const std::string& Book::GetDefaultCurrencyIsoCode() const
{
	return m_defaultCurrencyIsoCode;
}

} // ns tb::models::bdo