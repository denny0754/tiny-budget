#include <tb/models/bdo/FinancialBook.hpp>

namespace tb::models::bdo
{

FinancialBook::FinancialBook(
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

const std::string& FinancialBook::GetIdentityGuid() const
{
	return m_identityGuid;
}

const std::string& FinancialBook::GetName() const
{
	return m_name;
}

const std::string& FinancialBook::GetDescription() const
{
	return m_description;
}

const std::string& FinancialBook::GetDefaultCurrencyIsoCode() const
{
	return m_defaultCurrencyIsoCode;
}

} // ns tb::models::bdo