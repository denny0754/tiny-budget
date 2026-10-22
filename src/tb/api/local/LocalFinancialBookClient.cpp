#include <tb/api/local/LocalFinancialBookClient.hpp>
#include <tb/tools/Logging.hpp>
#include <tb/models/dbo/Dbo.hpp>

#include <Wt/Dbo/Dbo.h>

namespace tb::api
{

void LocalFinancialBookClient::CreateFinancialBook(
	const tb::models::dto::CreateFinancialBookRequest& data,
	tb::models::dto::APICallback<tb::models::dto::CreateFinancialBookResponse> callback
)
{
    tb::models::dto::APIResult<tb::models::dto::CreateFinancialBookResponse> result{};

    try
    {
        auto session = GetDatabaseSession();
        Wt::Dbo::Transaction dboTx(*session);

        std::string activeIdentityId = GetSessionContext()->IdentityId;
        auto identityPtr = session->find<tb::models::dbo::Identity>()
            .where("guid = ?").bind(activeIdentityId)
            .resultValue();

        if (!identityPtr)
        {
            result.Success = false;
            result.ErrorMessage = "No active user identity found.";
            callback(result);
            return;
        }

        auto book = std::make_unique<tb::models::dbo::FinancialBook>();
        book->SetName(data.Name);
        book->SetDescription(data.Description);
        book->SetIdentity(identityPtr);

        auto addedBookPtr = session->add(std::move(book));
        dboTx.commit();

        result.Success = true;
        result.Result.FinancialBookId = addedBookPtr->GetId();

        tb::tools::log::GetApiLogger()->info("Financial Book created with ID: {}", addedBookPtr->GetId());
    }
    catch (const std::exception& ex)
    {
        result.Success = false;
        result.ErrorMessage = std::string("Failed to create financial book: ") + ex.what();
    }

    callback(result);
}

void LocalFinancialBookClient::GetFinancialBookById(
	const std::string& id,
	tb::models::dto::APICallback<tb::models::dto::GetFinancialBookResponse> callback
)
{
    tb::models::dto::APIResult<tb::models::dto::GetFinancialBookResponse> result{};

    try
    {
        auto session = GetDatabaseSession();
        Wt::Dbo::Transaction dboTx(*session);

        auto bookPtr = session->find<tb::models::dbo::FinancialBook>()
            .where("guid = ?").bind(id)
            .resultValue();

        if (!bookPtr)
        {
            result.Success = false;
            result.ErrorMessage = "Financial book not found.";
            callback(result);
            return;
        }

        result.Success = true;
        result.Result.Id = bookPtr->GetId();
        result.Result.Name = bookPtr->GetName();
        result.Result.Description = bookPtr->GetDescription();
        result.Result.DefaultCurrencyCode = "EUR"; // Static default for now

        dboTx.commit();
    }
    catch (const std::exception& ex)
    {
        result.Success = false;
        result.ErrorMessage = std::string("Failed to retrieve financial book: ") + ex.what();
    }

    callback(result);
}

void LocalFinancialBookClient::GetFinancialBooks(
	const tb::models::dto::APIQueryParams& params,
	tb::models::dto::PaginatedAPICallback<tb::models::dto::GetFinancialBookResponse> callback
)
{
    tb::tools::log::GetApiLogger()->info("Requesting: GET /v1/book");
    tb::tools::log::GetApiLogger()->info("Current Identity ID: ", GetSessionContext()->IdentityId);

    tb::models::dto::PaginatedAPIResult<tb::models::dto::GetFinancialBookResponse> result{};

    try
    {
        auto session = GetDatabaseSession();
        Wt::Dbo::Transaction dboTx(*session);

        std::string activeIdentityId = GetSessionContext()->IdentityId;
        auto query = session->find<tb::models::dbo::FinancialBook>()
            .where("identity_id = ?").bind(activeIdentityId);

        // Apply search filter if provided
        auto nameFilterIt = params.Filters.find("name");
        if (nameFilterIt != params.Filters.end() && !nameFilterIt->second.empty())
        {
            query.where("name LIKE ?").bind("%" + nameFilterIt->second + "%");
        }

        // Apply pagination offsets
        int offset = static_cast<int>(params.Page * params.PageSize);
        auto dboBooks = query.orderBy("created_on DESC")
            .offset(offset)
            .limit(static_cast<int>(params.PageSize))
            .resultList();

        std::vector<tb::models::dto::GetFinancialBookResponse> bookDtos;
        bookDtos.reserve(dboBooks.size());

        for (const auto& bookPtr : dboBooks)
        {
            tb::models::dto::GetFinancialBookResponse dto;
            dto.Id = bookPtr->GetId();
            dto.Name = bookPtr->GetName();
            dto.Description = bookPtr->GetDescription();
            dto.DefaultCurrencyCode = "EUR";
            bookDtos.push_back(std::move(dto));
            tb::tools::log::GetApiLogger()->info("Found book with ID {}", dto.Id);
        }

        dboTx.commit();

        result.Success = true;
        result.Result = std::move(bookDtos);
    }
    catch (const std::exception& ex)
    {
        result.Success = false;
        result.ErrorMessage = std::string("Failed to query financial books: ") + ex.what();
    }

    callback(result);
}

} // ns tb::api