#ifndef TB_MODELS_BDO_FINANCIAL_BOOK_HPP
#define TB_MODELS_BDO_FINANCIAL_BOOK_HPP

#include <tb/models/bdo/Common.hpp>

namespace tb::models::bdo
{

class FinancialBook : public tb::models::bdo::BaseDataObject
{
public:
	FinancialBook(
		const std::string& guid,
		const std::chrono::system_clock::time_point& created_on,
		const std::chrono::system_clock::time_point& updated_on,
		const std::string& identity_guid,
		const std::string& name,
		const std::string& description,
		const std::string& dflt_currency_iso_code
	);

	const std::string& GetIdentityGuid() const;

	const std::string& GetName() const;

	const std::string& GetDescription() const;

	const std::string& GetDefaultCurrencyIsoCode() const;

private:
	std::string m_identityGuid;
	std::string m_name;
	std::string m_description;
	std::string m_defaultCurrencyIsoCode;
};

} // ns tb::models::bdo

#endif