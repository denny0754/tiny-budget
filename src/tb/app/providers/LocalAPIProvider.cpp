#include <tb/app/providers/LocalAPIProvider.hpp>
#include <tb/models/dbo/Dbo.hpp>
#include <tb/tools/Security.hpp>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>

#include <filesystem>

namespace tb::app::providers
{

LocalAPIProvider::LocalAPIProvider()
{
	m_dbSession = std::make_unique<Wt::Dbo::Session>();

	std::filesystem::create_directory("./data");

	auto sqliteBackend = std::make_unique<Wt::Dbo::backend::Sqlite3>("data/db.sqlite");
	m_dbSession->setConnection(std::move(sqliteBackend));

	m_dbSession->mapClass<tb::models::dbo::Identity>("identity");
	m_dbSession->mapClass<tb::models::dbo::PasswordCredential>("password_credential");
	m_dbSession->mapClass<tb::models::dbo::FinancialBook>("financial_book");
	m_dbSession->mapClass<tb::models::dbo::Partner>("partner");
	m_dbSession->mapClass<tb::models::dbo::PartnerAddress>("partner_address");
	m_dbSession->mapClass<tb::models::dbo::PartnerCommunication>("partner_communication");
	m_dbSession->mapClass<tb::models::dbo::Account>("account");
	m_dbSession->mapClass<tb::models::dbo::Transaction>("transaction");
	m_dbSession->mapClass<tb::models::dbo::TransactionItem>("transaction_item");
	m_dbSession->mapClass<tb::models::dbo::Product>("product");
	m_dbSession->mapClass<tb::models::dbo::CodeList>("code_list");

	try
	{
		Wt::Dbo::Transaction trx{ *m_dbSession };
		m_dbSession->createTables();
		trx.commit();
	}
	catch (Wt::Dbo::Exception& e)
	{
		GetLogger()->critical("Error while initializing SQLite3 Backend...");
		GetLogger()->error("Wt::Dbo Exception: {}", e.what());
	}
}

void LocalAPIProvider::SignUp(
	const tb::models::dto::SignUpRequest& data,
	APIProvider::APICallback<tb::models::dto::SignUpResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::SignUpResponse> result;

	try
	{
		Wt::Dbo::Transaction trx{ *m_dbSession };

		int count = m_dbSession->query<int>("select count(*) from identity")
			.where("email = ?")
			.bind(data.Email);

		if (count > 0)
		{
			result.Success = false;
			result.ErrorMessage = "An account with this email address already exists.";
			callback(result);
			return;
		}

		auto identity = std::make_unique<tb::models::dbo::Identity>();
		auto credential = std::make_unique<tb::models::dbo::PasswordCredential>();

		auto currentDateTime = Wt::WDateTime::currentDateTime();
		identity->SetFirstName(data.FirstName);
		identity->SetLastName(data.LastName);
		identity->SetEmail(data.Email);
		auto identityPtr = m_dbSession->add(std::move(identity));

		std::string pwd_hash = tb::tools::Security::HashPassword(data.Password);
		credential->SetPasswordHash(pwd_hash);
		credential->SetIdentity(identityPtr);
		m_dbSession->add(std::move(credential));

		trx.commit();

		result.Success = true;
		result.Result.Email = data.Email;
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Error while trying to write to the Database...";
		GetLogger()->error("Wt::Dbo Exception: {}", e.what());
	}

	callback(result);
}

void LocalAPIProvider::SignIn(
	const tb::models::dto::SignInRequest& data,
	APIProvider::APICallback<tb::models::dto::SignInResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::SignInResponse> result;
	result.Success = false;
	result.ErrorMessage = "Invalid email or password."; // Default fallback error

	try
	{
		Wt::Dbo::Transaction trx{ *m_dbSession };

		auto identities = m_dbSession->find<tb::models::dbo::Identity>()
			.where("email = ?")
			.bind(data.Email)
			.resultList();

		if (!identities.empty())
		{
			auto identity = identities.front();
			auto credentialPtr = identity->GetPasswordCredential();

			if (credentialPtr)
			{
				std::string stored_hash = credentialPtr->GetPasswordHash();

				bool isPasswordValid = tb::tools::Security::VerifyPasswordHash(
					data.Password,
					stored_hash
				);

				if (isPasswordValid)
				{
					result.Success = true;
					result.ErrorMessage = "";
					result.Result.Email = identity->GetEmail();
					result.Result.FirstName = identity->GetFirstName();
					result.Result.LastName = identity->GetLastName();
					result.Result.IdentityId = identity->GetId();
				}
			}
		}
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Database error while processing sign-in.";
	}

	callback(result);
}

} // ns tb::app::providers