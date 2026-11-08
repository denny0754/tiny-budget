#include <tb/api/BookClient.hpp>
#include <tb/tools/Logging.hpp>
#include <tb/models/dbo/Dbo.hpp>

#include <Wt/Dbo/Dbo.h>

#include <format>

namespace tb::api
{

void BookClient::Create(
	const tb::models::dto::CreateBookRequest& data,
	tb::models::dto::APICallback<tb::models::dto::CreateBookResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::CreateBookResponse> result;

	try
	{
		auto session = GetDatabaseSession();
		Wt::Dbo::Transaction trx{ *session };

		auto currencyRec = session->find<tb::models::dbo::Currency>()
			.where("iso_code = ?")
			.bind(data.DefaultCurrencyIsoCode)
			.resultValue();

		if (!currencyRec)
		{
			result.Success = false;
			result.ErrorMessage = std::format("Currency code '{}' is invalid.", data.DefaultCurrencyIsoCode);
			callback(result);
			return;
		}

		auto identityRec = session->find<tb::models::dbo::Identity>()
			.where("guid = ?")
			.bind(GetSessionContext()->IdentityId)
			.resultValue();

		if (!identityRec)
		{
			result.Success = false;
			result.ErrorMessage = "User is not authorized or identity was not found.";
			callback(result);
			return;
		}

		auto rawBook = std::make_unique<tb::models::dbo::FinancialBook>();
		rawBook->SetName(data.Name);
		rawBook->SetDescription(data.Description);
		rawBook->SetDefaultCurrency(currencyRec);
		rawBook->SetIdentity(identityRec);

		Wt::Dbo::ptr<tb::models::dbo::FinancialBook> bookPtr = session->add(std::move(rawBook));
		trx.commit();

		result.Success = true;
		result.Data.Id = bookPtr.id();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error while creating financial book.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception in BookClient::Create: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception in BookClient::Create: {}", e.what());
	}

	callback(result);
}

void BookClient::UpdateById(
	const std::string& id,
	const tb::models::dto::UpdateBookRequest& data,
	tb::models::dto::APICallback<tb::models::dto::UpdateBookResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::UpdateBookResponse> result;

	try
	{
		auto session = GetDatabaseSession();
		Wt::Dbo::Transaction trx{ *session };

		auto bookRec = session->find<tb::models::dbo::FinancialBook>()
			.where("guid = ? AND identity_id = ?")
			.bind(id)
			.bind(GetSessionContext()->IdentityId)
			.resultValue();

		if (!bookRec)
		{
			result.Success = false;
			result.ErrorMessage = std::format("Book with ID '{}' not found or access denied.", id);
			callback(result);
			return;
		}

		Wt::Dbo::ptr<tb::models::dbo::Currency> currencyRec;
		if (!data.DefaultCurrencyIsoCode.empty())
		{
			currencyRec = session->find<tb::models::dbo::Currency>()
				.where("iso_code = ?")
				.bind(data.DefaultCurrencyIsoCode);

			if (!currencyRec)
			{
				result.Success = false;
				result.ErrorMessage = std::format("Currency code '{}' is invalid.", data.DefaultCurrencyIsoCode);
				callback(result);
				return;
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

		result.Success = true;
		result.Data.Id = bookRec.id();
		result.Data.Name = bookRec->GetName();
		result.Data.Description = bookRec->GetDescription();
		if (bookRec->GetDefaultCurrency())
		{
			result.Data.DefaultCurrencyIsoCode = bookRec->GetDefaultCurrency()->GetIsoCode();
		}
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error while updating financial book.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception in BookClient::UpdateById: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception in BookClient::UpdateById: {}", e.what());
	}

	callback(result);
}

void BookClient::GetById(
	const std::string& id,
	tb::models::dto::APICallback<tb::models::dto::GetBookResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::GetBookResponse> result;

	try
	{
		auto session = GetDatabaseSession();
		Wt::Dbo::Transaction trx{ *session };

		auto bookRec = session->find<tb::models::dbo::FinancialBook>()
			.where("guid = ? AND identity_id = ?")
			.bind(id)
			.bind(GetSessionContext()->IdentityId)
			.resultValue();

		if (!bookRec)
		{
			result.Success = false;
			result.ErrorMessage = std::format("Book with ID '{}' not found or access denied.", id);
			callback(result);
			return;
		}

		result.Success = true;
		result.Data.Id = bookRec.id();
		result.Data.Name = bookRec->GetName();
		result.Data.Description = bookRec->GetDescription();
		if (bookRec->GetDefaultCurrency())
		{
			result.Data.DefaultCurrencyIsoCode = bookRec->GetDefaultCurrency()->GetIsoCode();
		}

		trx.commit();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error while fetching financial book.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception in BookClient::GetById: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception in BookClient::GetById: {}", e.what());
	}

	callback(result);
}

void BookClient::GetAny(
	const tb::models::dto::APIQueryParams& params,
	tb::models::dto::PaginatedAPICallback<tb::models::dto::GetBookResponse> callback
)
{
	tb::models::dto::PaginatedAPIResult<tb::models::dto::GetBookResponse> result;

	try
	{
		auto session = GetDatabaseSession();
		Wt::Dbo::Transaction trx{ *session };

		auto query = session->find<tb::models::dbo::FinancialBook>()
			.where("identity_id = ?")
			.bind(GetSessionContext()->IdentityId);

		for (const auto& [key, value] : params.Filters)
		{
			if (key == "name")
			{
				query.where("name LIKE ?").bind("%" + value + "%");
			}
			else if (key == "description")
			{
				query.where("description LIKE ?").bind("%" + value + "%");
			}
		}

		const unsigned int offset = params.Page * params.PageSize;
		query.offset(static_cast<int>(offset))
			.limit(static_cast<int>(params.PageSize));

		auto books = query.resultList();
		result.Data.reserve(books.size());

		for (const auto& bookRec : books)
		{
			tb::models::dto::GetBookResponse dto;
			dto.Id = bookRec.id();
			dto.Name = bookRec->GetName();
			dto.Description = bookRec->GetDescription();
			if (bookRec->GetDefaultCurrency())
			{
				dto.DefaultCurrencyIsoCode = bookRec->GetDefaultCurrency()->GetIsoCode();
			}

			result.Data.push_back(std::move(dto));
		}

		trx.commit();
		result.Success = true;
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error while fetching financial books.";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception in BookClient::GetAny: {}", e.what());
	}
	catch (const std::exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "An unexpected error occurred.";
		tb::tools::log::GetApiLogger()->error("Unhandled Exception in BookClient::GetAny: {}", e.what());
	}

	callback(result);
}

} // ns tb::api