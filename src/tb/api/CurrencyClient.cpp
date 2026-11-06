#include <tb/api/CurrencyClient.hpp>
#include <tb/models/dbo/Dbo.hpp>
#include <tb/tools/Logging.hpp>

#include <Wt/Dbo/Dbo.h>

namespace tb::api
{

void CurrencyClient::Create(
	const tb::models::dto::CreateCurrencyRequest& data,
	tb::models::dto::APICallback<tb::models::dto::CreateCurrencyResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::CreateCurrencyResponse> result;

	try
	{
		Wt::Dbo::Transaction trx{ *GetDatabaseSession() };

		auto existingCurrency = session->find<tb::models::dbo::Currency>()
			.where("isoCode = ?")
			.bind(data.IsoCode);

		if (existingCurrency)
		{
			result.Success = false;
			result.ErrorMessage = std::format("Currency with ISO code '{}' already exists.", data.IsoCode);
			callback(result);
			return;
		}

		auto rawCurrency = std::make_unique<tb::models::dbo::Currency>();
		rawCurrency->SetIsoCode(data.IsoCode);
		rawCurrency->SetName(data.Name);
		rawCurrency->SetSymbol(data.Symbol);

		Wt::Dbo::ptr<tb::models::dbo::Currency> currencyPtr = session->add(std::move(rawCurrency));
		trx.commit();

		result.Success = true;
		result.Data.Id = currencyPtr.id();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error occurred while creating currency.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	callback(result);
}

void CurrencyClient::UpdateById(
	const std::string& id,
	const tb::models::dto::UpdateCurrencyRequest& data,
	tb::models::dto::APICallback<tb::models::dto::UpdateCurrencyResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::UpdateCurrencyResponse> result;

	try
	{
		Wt::Dbo::Transaction trx{ *GetDatabaseSession() };

		auto currencyRec = session->find<tb::models::dbo::Currency>()
			.where("id = ?")
			.bind(id);

		if (!currencyRec)
		{
			result.Success = false;
			result.ErrorMessage = std::format("Currency with ID '{}' not found.", id);
			callback(result);
			return;
		}

		auto duplicateIso = session->find<tb::models::dbo::Currency>()
			.where("isoCode = ? AND id != ?")
			.bind(data.IsoCode)
			.bind(id);

		if (duplicateIso)
		{
			result.Success = false;
			result.ErrorMessage = std::format("ISO code '{}' is already in use by another currency.", data.IsoCode);
			callback(result);
			return;
		}

		{
			auto currency = currencyRec.modify();
			currency->SetIsoCode(data.IsoCode);
			currency->SetName(data.Name);
			currency->SetSymbol(data.Symbol);
		}

		trx.commit();

		result.Success = true;
		result.Data.Id = currencyRec.id();
		result.Data.IsoCode = currencyRec->GetIsoCode();
		result.Data.Name = currencyRec->GetName();
		result.Data.Symbol = currencyRec->GetSymbol();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error occurred while updating currency by ID.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception in UpdateById: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception in UpdateById: {}", e.what());
	}

	callback(result);
}

void CurrencyClient::UpdateByIsoCode(
	const std::string& isoCode,
	const tb::models::dto::UpdateCurrencyRequest& data,
	tb::models::dto::APICallback<tb::models::dto::UpdateCurrencyResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::UpdateCurrencyResponse> result;

	try
	{
		Wt::Dbo::Transaction trx{ *GetDatabaseSession() };

		auto currencyRec = session->find<tb::models::dbo::Currency>()
			.where("isoCode = ?")
			.bind(isoCode);

		if (!currencyRec)
		{
			result.Success = false;
			result.ErrorMessage = std::format("Currency with ISO code '{}' not found.", targetIsoCode);
			callback(result);
			return;
		}

		auto duplicateIso = session->find<tb::models::dbo::Currency>()
			.where("isoCode = ? AND id != ?")
			.bind(data.IsoCode)
			.bind(currencyRec.id());

		if (duplicateIso)
		{
			result.Success = false;
			result.ErrorMessage = std::format("ISO code '{}' is already in use by another currency.", data.IsoCode);
			callback(result);
			return;
		}

		{
			auto currency = currencyRec.modify();
			currency->SetIsoCode(data.IsoCode);
			currency->SetName(data.Name);
			currency->SetSymbol(data.Symbol);
		}

		trx.commit();

		result.Success = true;
		result.Data.Id = currencyRec.id();
		result.Data.IsoCode = currencyRec->GetIsoCode();
		result.Data.Name = currencyRec->GetName();
		result.Data.Symbol = currencyRec->GetSymbol();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error occurred while updating currency by ISO code.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	callback(result);
}

void CurrencyClient::DeleteById(
	const std::string& id,
	tb::models::dto::APICallback<tb::models::dto::DeleteCurrencyResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::DeleteCurrencyResponse> result;

	try
	{
		Wt::Dbo::Transaction trx{ *GetDatabaseSession() };

		auto currencyRec = session->find<tb::models::dbo::Currency>()
			.where("id = ?")
			.bind(id);

		if (!currencyRec)
		{
			result.Success = false;
			result.ErrorMessage = std::format("Currency with ID '{}' not found.", id);
			callback(result);
			return;
		}

		currencyRec.purge();
		trx.commit();

		result.Success = true;
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error occurred while deleting currency by ID.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	callback(result);
}

void CurrencyClient::DeleteByIsoCode(
	const std::string& isoCode,
	tb::models::dto::APICallback<tb::models::dto::DeleteCurrencyResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::DeleteCurrencyResponse> result;

	try
	{
		Wt::Dbo::Transaction trx{ *GetDatabaseSession() };

		auto currencyRec = session->find<tb::models::dbo::Currency>()
			.where("isoCode = ?")
			.bind(isoCode);

		if (!currencyRec)
		{
			result.Success = false;
			result.ErrorMessage = std::format("Currency with ISO code '{}' not found.", isoCode);
			callback(result);
			return;
		}

		currencyRec.purge();
		trx.commit();

		result.Success = true;
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error occurred while deleting currency by ISO code.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	callback(result);
}

void CurrencyClient::GetById(
	const std::string& id,
	tb::models::dto::APICallback<tb::models::dto::GetCurrencyResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::GetCurrencyResponse> result;

	try
	{
		Wt::Dbo::Transaction trx{ *GetDatabaseSession() };

		auto currencyRec = GetDatabaseSession()->find<tb::models::dbo::Currency>()
			.where("id = ?")
			.bind(id)
			.resultValue();

		if (currencyRec)
		{
			result.Success = true;
			result.ErrorMessage = std::string("");
			result.Data.Id = currencyRec->GetId();
			result.Data.IsoCode = currencyRec->GetIsoCode();
			result.Data.Label = currencyRec->GetLabel();
			result.Data.Symbol = currencyRec->GetSymbol();
		}
		else
		{
			result.Success = false;
			result.ErrorMessage = std::format("Currency with id {} not found.", id);
		}

		trx.commit();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Error while trying to write to the Database...";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	callback(result);
}

void CurrencyClient::GetByIsoCode(
	const std::string& isoCode,
	tb::models::dto::APICallback<tb::models::dto::GetCurrencyResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::GetCurrencyResponse> result;

	try
	{
		Wt::Dbo::Transaction trx{ *GetDatabaseSession() };

		auto currencyRec = GetDatabaseSession()->find<tb::models::dbo::Currency>()
			.where("iso_code = ?")
			.bind(isoCode)
			.resultValue();

		if (currencyRec)
		{
			result.Success = true;
			result.ErrorMessage = std::string("");
			result.Data.Id = currencyRec->GetId();
			result.Data.IsoCode = currencyRec->GetIsoCode();
			result.Data.Label = currencyRec->GetLabel();
			result.Data.Symbol = currencyRec->GetSymbol();
		}
		else
		{
			result.Success = false;
			result.ErrorMessage = std::format("Currency with ISO Code {} not found.", isoCode);
		}

		trx.commit();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Error while trying to write to the Database...";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	callback(result);
}

void CurrencyClient::GetAny(
	const tb::models::dto::APIQueryParams& params,
	tb::models::dto::PaginatedAPICallback<tb::models::dto::GetCurrencyResponse> callback
)
{
	tb::models::dto::PaginatedAPIResult<tb::models::dto::GetCurrencyResponse> result;

	try
	{
		Wt::Dbo::Transaction trx{ *GetDatabaseSession() };

		auto query = session->find<tb::models::dbo::Currency>();

		for (const auto& [key, value] : params.Filters)
		{
			if (key == "isoCode")
			{
				query.where("isoCode LIKE ?").bind("%" + value + "%");
			}
			else if (key == "name")
			{
				query.where("name LIKE ?").bind("%" + value + "%");
			}
			else if (key == "symbol")
			{
				query.where("symbol LIKE ?").bind("%" + value + "%");
			}
		}

		const unsigned int offset = params.Page * params.PageSize;
		query.offset(static_cast<int>(offset))
			.limit(static_cast<int>(params.PageSize));

		auto currencies = query.resultList();
		result.Data.reserve(currencies.size());

		for (const auto& currencyRec : currencies)
		{
			tb::models::dto::GetCurrencyResponse currency;
			currency.Id = currencyRec.id();
			currency.IsoCode = currencyRec->GetIsoCode();
			currency.Name = currencyRec->GetName();
			currency.Symbol = currencyRec->GetSymbol();

			result.Data.push_back(std::move(currency));
		}

		trx.commit();
		result.Success = true;
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error while fetching currencies.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception: {}", e.what());
	}

	callback(result);
}

} // ns tb::api