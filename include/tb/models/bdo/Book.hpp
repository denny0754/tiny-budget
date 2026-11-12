/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-10 | Diego Vaccher | UI-0000006-M  | Visualize Active Books on Side Menu
================================================================================
*/

#ifndef TB_MODELS_BDO_BOOK_HPP
#define TB_MODELS_BDO_BOOK_HPP

#include <tb/models/bdo/Common.hpp>

namespace tb::models::bdo
{

class Book : public tb::models::bdo::BaseDataObject
{
public:
	Book(
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
}; // cl Book

} // ns tb::models::bdo

#endif