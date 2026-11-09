/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#include <tb/api/CurrencyClient.hpp>
#include <tb/models/dbo/Dbo.hpp>
#include <tb/tools/Logging.hpp>

#include <Wt/Dbo/Dbo.h>

namespace tb::api
{

tb::models::dto::CreateCurrencyResponse CurrencyClient::Create(
	const tb::models::dto::CreateCurrencyRequest& data
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	tb::models::dto::CreateCurrencyResponseData responseData{};

	try
	{
		auto dbSession = GetDbSession();

		Wt::Dbo::Transaction trx{ *dbSession };

		auto existingCurrency = dbSession->find<tb::models::dbo::Currency>()
			.where("isoCode = ?")
			.bind(data.IsoCode)
			.resultValue();

		if (existingCurrency)
		{
			error = true;
			errorMsg = std::format("Currency with ISO code '{}' already exists.", data.IsoCode);
		}
		else
		{
			auto rawCurrency = std::make_unique<tb::models::dbo::Currency>();
			rawCurrency->SetIsoCode(data.IsoCode);
			rawCurrency->SetName(data.Label);
			rawCurrency->SetSymbol(data.Symbol);

			Wt::Dbo::ptr<tb::models::dbo::Currency> currencyPtr = dbSession->add(std::move(rawCurrency));
			trx.commit();

			error = false;
			responseData.Guid = currencyPtr.id();
		}
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error occurred while creating currency.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	return tb::models::dto::CreateCurrencyResponse({ responseData }, 0, error, errorMsg);
}

tb::models::dto::UpdateCurrencyResponse CurrencyClient::UpdateById(
	const std::string& id,
	const tb::models::dto::UpdateCurrencyRequest& data
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	tb::models::dto::UpdateCurrencyResponseData responseData{};

	try
	{
		auto dbSession = GetDbSession();

		Wt::Dbo::Transaction trx{ *dbSession };

		auto currencyRec = dbSession->find<tb::models::dbo::Currency>()
			.where("id = ?")
			.bind(id)
			.resultValue();

		if (!currencyRec)
		{
			error = true;
			errorMsg = std::format("Currency with ID '{}' not found.", id);
		}
		else
		{
			auto duplicateIso = dbSession->find<tb::models::dbo::Currency>()
				.where("isoCode = ? AND id != ?")
				.bind(data.IsoCode)
				.bind(id)
				.resultValue();

			if (duplicateIso)
			{
				error = true;
				errorMsg = std::format("ISO code '{}' is already in use by another currency.", data.IsoCode);
			}
			else
			{
				auto currency = currencyRec.modify();
				currency->SetIsoCode(data.IsoCode);
				currency->SetName(data.Label);
				currency->SetSymbol(data.Symbol);

				trx.commit();

				error = false;
				responseData.IsoCode = currencyRec->GetIsoCode();
				responseData.Label = currencyRec->GetLabel();
				responseData.Symbol = currencyRec->GetSymbol();
				responseData.Guid = currencyRec.id();
			}

		}
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg  = "Database error occurred while updating currency by ID.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception in UpdateById: {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception in UpdateById: {}", e.what());
	}

	return tb::models::dto::UpdateCurrencyResponse({ responseData }, 0, error, errorMsg);
}

tb::models::dto::UpdateCurrencyResponse CurrencyClient::UpdateByIsoCode(
	const std::string& isoCode,
	const tb::models::dto::UpdateCurrencyRequest& data
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	tb::models::dto::UpdateCurrencyResponseData responseData{};

	try
	{
		auto dbSession = GetDbSession();

		Wt::Dbo::Transaction trx{ *dbSession };

		auto currencyRec = dbSession->find<tb::models::dbo::Currency>()
			.where("isoCode = ?")
			.bind(isoCode)
			.resultValue();

		if (!currencyRec)
		{
			error = true;
			errorMsg = std::format("Currency with ISO code '{}' not found.", isoCode);
		}
		else
		{
			auto duplicateIso = dbSession->find<tb::models::dbo::Currency>()
				.where("isoCode = ? AND id != ?")
				.bind(data.IsoCode)
				.bind(currencyRec->GetId())
				.resultValue();

			if (duplicateIso)
			{
				error = true;
				errorMsg = std::format("ISO code '{}' is already in use by another currency.", data.IsoCode);
			}
			else
			{
				auto currency = currencyRec.modify();
				currency->SetIsoCode(data.IsoCode);
				currency->SetName(data.Label);
				currency->SetSymbol(data.Symbol);

				trx.commit();

				error = false;
				errorMsg = std::string();
				responseData.IsoCode = currencyRec->GetIsoCode();
				responseData.Label = currencyRec->GetLabel();
				responseData.Symbol = currencyRec->GetSymbol();
				responseData.Guid = currencyRec.id();
			}
		}
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error occurred while updating currency by ISO code.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	return tb::models::dto::UpdateCurrencyResponse({ responseData }, 0, error, errorMsg);
}

tb::models::dto::DeleteCurrencyResponse CurrencyClient::Delete(
	const std::string& id
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	tb::models::dto::DeleteCurrencyResponseData responseData{};

	try
	{
		auto dbSession = GetDbSession();

		Wt::Dbo::Transaction trx{ *dbSession };

		auto currencyRec = dbSession->find<tb::models::dbo::Currency>()
			.where("id = ?")
			.bind(id)
			.resultValue();

		if (!currencyRec)
		{
			error = true;
			errorMsg = std::format("Currency with ID '{}' not found.", id);
		}
		else
		{
			currencyRec.purge();
			error = false;
			errorMsg = std::string("");
		}

		trx.commit();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error occurred while deleting currency by ID.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	return tb::models::dto::DeleteCurrencyResponse({ responseData }, 0, error, errorMsg);
}

tb::models::dto::GetCurrencyResponse CurrencyClient::GetById(
	const std::string& id
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	tb::models::dto::GetCurrencyResponseData responseData{};

	try
	{
		auto dbSession = GetDbSession();

		Wt::Dbo::Transaction trx{ *dbSession };

		auto currencyRec = dbSession->find<tb::models::dbo::Currency>()
			.where("id = ?")
			.bind(id)
			.resultValue();

		if (currencyRec)
		{
			error = false;
			errorMsg = std::string("");
			responseData.Guid = currencyRec->GetId();
			responseData.IsoCode = currencyRec->GetIsoCode();
			responseData.Label = currencyRec->GetLabel();
			responseData.Symbol = currencyRec->GetSymbol();
		}
		else
		{
			error = true;
			errorMsg = std::format("Currency with id {} not found.", id);
		}

		trx.commit();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Error while trying to write to the Database...";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	return tb::models::dto::GetCurrencyResponse({ responseData }, 0, error, errorMsg);
}

tb::models::dto::GetCurrencyResponse CurrencyClient::GetByIsoCode(
	const std::string& isoCode
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	tb::models::dto::GetCurrencyResponseData responseData{};

	try
	{
		auto dbSession = GetDbSession();

		Wt::Dbo::Transaction trx{ *dbSession };

		auto currencyRec = dbSession->find<tb::models::dbo::Currency>()
			.where("iso_code = ?")
			.bind(isoCode)
			.resultValue();

		if (currencyRec)
		{
			error = false;
			errorMsg = std::string("");
			responseData.Guid = currencyRec->GetId();
			responseData.IsoCode = currencyRec->GetIsoCode();
			responseData.Label = currencyRec->GetLabel();
			responseData.Symbol = currencyRec->GetSymbol();
		}
		else
		{
			error = true;
			errorMsg = std::format("Currency with ISO Code {} not found.", isoCode);
		}

		trx.commit();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error while fetching currencies.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	return tb::models::dto::GetCurrencyResponse({ responseData }, 0, error, errorMsg);
}

tb::models::dto::GetCurrencyResponse CurrencyClient::GetAny(
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	std::vector<tb::models::dto::GetCurrencyResponseData> responseData{};

	try
	{
		auto dbSession = GetDbSession();

		Wt::Dbo::Transaction trx{ *dbSession };

		auto query = dbSession->find<tb::models::dbo::Currency>();

		auto currencies = query.resultList();
		
		for (const auto& currencyRec : currencies)
		{
			tb::models::dto::GetCurrencyResponseData currency;
			currency.Guid = currencyRec.id();
			currency.IsoCode = currencyRec->GetIsoCode();
			currency.Label = currencyRec->GetLabel();
			currency.Symbol = currencyRec->GetSymbol();

			responseData.push_back(std::move(currency));
		}

		trx.commit();
		error = false;
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error while fetching currencies.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	return tb::models::dto::GetCurrencyResponse(responseData, 0, error, errorMsg);
}

} // ns tb::api