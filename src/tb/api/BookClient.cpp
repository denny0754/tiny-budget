/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#include <tb/api/BookClient.hpp>
#include <tb/tools/Logging.hpp>
#include <tb/models/dbo/Dbo.hpp>

#include <Wt/Dbo/Dbo.h>

#include <format>

namespace tb::api
{

tb::models::dto::CreateBookResponse BookClient::Create(
	const tb::models::dto::CreateBookRequest& data
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	tb::models::dto::CreateBookResponseData responseData{};

	try
	{
		auto dbSession = GetDbSession();
		Wt::Dbo::Transaction trx{ *dbSession };

		auto currencyRec = dbSession->find<tb::models::dbo::Currency>()
			.where("iso_code = ?")
			.bind(data.DefaultCurrencyIsoCode)
			.resultValue();

		if (!currencyRec)
		{
			error = true;
			errorMsg = std::format("Currency code '{}' is invalid.", data.DefaultCurrencyIsoCode);
		}
		else
		{
			auto identityRec = dbSession->find<tb::models::dbo::Identity>()
				.where("guid = ?")
				.bind(GetSessionCtx()->IdentityId)
				.resultValue();

			if (!identityRec)
			{
				error = true;
				errorMsg = "User is not authorized or identity was not found.";
			}
			else
			{
				auto rawBook = std::make_unique<tb::models::dbo::FinancialBook>();
				rawBook->SetName(data.Name);
				rawBook->SetDescription(data.Description);
				rawBook->SetDefaultCurrency(currencyRec);
				rawBook->SetIdentity(identityRec);

				Wt::Dbo::ptr<tb::models::dbo::FinancialBook> bookPtr = dbSession->add(std::move(rawBook));
				trx.commit();

				error = false;
				responseData.Guid = bookPtr.id();
			}
		}
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error while creating financial book.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception in BookClient::Create: {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception in BookClient::Create: {}", e.what());
	}

	return tb::models::dto::CreateBookResponse({ responseData }, 0, error, errorMsg);
}

tb::models::dto::UpdateBookResponse BookClient::UpdateById(
	const std::string& id,
	const tb::models::dto::UpdateBookRequest& data
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	tb::models::dto::UpdateBookResponseData responseData{};

	try
	{
		auto dbSession = GetDbSession();
		Wt::Dbo::Transaction trx{ *dbSession };

		auto bookRec = dbSession->find<tb::models::dbo::FinancialBook>()
			.where("guid = ? AND identity_id = ?")
			.bind(id)
			.bind(GetSessionCtx()->IdentityId)
			.resultValue();

		if (!bookRec)
		{
			error = true;
			errorMsg = std::format("Book with ID '{}' not found or access denied.", id);
		}
		else
		{
			Wt::Dbo::ptr<tb::models::dbo::Currency> currencyRec;
			if (!data.CurrencyGuid.empty())
			{
				currencyRec = dbSession->find<tb::models::dbo::Currency>()
					.where("guid = ?")
					.bind(data.CurrencyGuid);

				if (!currencyRec)
				{
					error = true;
					errorMsg = std::format("Currency '{}' is invalid.", data.CurrencyGuid);
				}
			}

			{
				auto book = bookRec.modify();
				book->SetName(data.Name);
				book->SetDescription(data.Description);
				if (currencyRec)
				{
					book->SetDefaultCurrency(currencyRec);
				}
			}

			trx.commit();

			error = false;
			responseData.Guid = bookRec.id();
			responseData.Name = bookRec->GetName();
			responseData.Description = bookRec->GetDescription();
			if (bookRec->GetDefaultCurrency())
			{
				responseData.CurrencyGuid = bookRec->GetDefaultCurrency()->GetId();
			}
		}
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error while updating financial book.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception in BookClient::UpdateById: {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception in BookClient::UpdateById: {}", e.what());
	}

	return tb::models::dto::UpdateBookResponse({ responseData }, 0, error, errorMsg);
}

tb::models::dto::GetBookResponse BookClient::GetById(
	const std::string& id
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	tb::models::dto::GetBookResponseData responseData{};

	try
	{
		auto dbSession = GetDbSession();
		Wt::Dbo::Transaction trx{ *dbSession };

		auto bookRec = dbSession->find<tb::models::dbo::FinancialBook>()
			.where("guid = ? AND identity_id = ?")
			.bind(id)
			.bind(GetSessionCtx()->IdentityId)
			.resultValue();

		if (!bookRec)
		{
			error = false;
			errorMsg = std::format("Book with ID '{}' not found or access denied.", id);
		}
		else
		{
			error = false;
			responseData.Guid = bookRec.id();
			responseData.Name = bookRec->GetName();
			responseData.Description = bookRec->GetDescription();
			if (bookRec->GetDefaultCurrency())
			{
				responseData.CurrencyGuid= bookRec->GetDefaultCurrency()->GetId();
			}

			trx.commit();
		}
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error while fetching financial book.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception in BookClient::GetById: {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception in BookClient::GetById: {}", e.what());
	}

	return tb::models::dto::GetBookResponse({ responseData }, 0, error, errorMsg);
}

tb::models::dto::GetBookResponse BookClient::GetAny(
)
{
	bool error{ false };
	std::string errorMsg{ "" };
	std::vector<tb::models::dto::GetBookResponseData> responseData{};

	try
	{
		auto dbSession = GetDbSession();
		Wt::Dbo::Transaction trx{ *dbSession };

		auto query = dbSession->find<tb::models::dbo::FinancialBook>()
			.where("identity_id = ?")
			.bind(GetSessionCtx()->IdentityId);

		auto books = query.resultList();
		
		for (const auto& bookRec : books)
		{
			tb::models::dto::GetBookResponseData dto;
			dto.Guid = bookRec.id();
			dto.Name = bookRec->GetName();
			dto.Description = bookRec->GetDescription();
			if (bookRec->GetDefaultCurrency())
			{
				dto.CurrencyGuid = bookRec->GetDefaultCurrency()->GetId();
			}

			responseData.push_back(std::move(dto));
		}

		trx.commit();
		error = false;
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error while fetching financial books.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception in BookClient::GetAny: {}", e.what());
	}
	catch (const std::exception& e)
	{
		error = true;
		errorMsg = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception in BookClient::GetAny: {}", e.what());
	}

	return tb::models::dto::GetBookResponse({ responseData }, 0, error, errorMsg);
}

} // ns tb::api