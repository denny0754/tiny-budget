#include <tb/api/BookClient.hpp>
#include <tb/models/dbo/Dbo.hpp>
#include <tb/tools/Logging.hpp>

#include <Wt/Dbo/Dbo.h>

namespace tb::api
{

void BookClient::CreateBook(
	const tb::models::dto::NewBookRequest& data,
	tb::models::dto::APICallback<tb::models::dto::NewBookResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::NewBookResponse> result;

	try
	{
		auto session = GetDatabaseSession();
		Wt::Dbo::Transaction trx{ *session };

		auto currencyRec = session->find<tb::models::dbo::Currency>()
			.where("isoCode = ?")
			.bind(data.DefaultCurrencyIsoCode)
			.resultValue();

		if (!currencyRec)
		{
			result.Success = false;
			result.ErrorMessage = std::format("Invalid currency code {}.", data.DefaultCurrencyIsoCode);
			callback(result);
			return;
		}

		auto identityRec = session->find<tb::models::dbo::Identity>()
			.where("id = ?")
			.bind(GetSessionContext()->IdentityId)
			.resultValue();

		if (!identityRec)
		{
			result.Success = false;
			result.ErrorMessage = "User is not authorized to perform this action.";
			callback(result);
			return;
		}

		auto rawBook = std::make_unique<tb::models::dbo::FinancialBook>();
		rawBook->SetDefaultCurrency(currencyRec);
		rawBook->SetDescription(data.Description);
		rawBook->SetName(data.Name);
		rawBook->SetIdentity(identityRec);

		Wt::Dbo::ptr<tb::models::dbo::FinancialBook> bookPtr = session->add(std::move(rawBook));
		trx.commit();

		result.Success = true;
		result.Data.BookId = bookPtr->GetId();
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

} // ns tb::api