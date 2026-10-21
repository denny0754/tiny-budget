#include <tb/api/local/LocalAuthClient.hpp>
#include <tb/models/dbo/Dbo.hpp>
#include <tb/tools/Security.hpp>
#include <tb/tools/Logging.hpp>

#include <Wt/Dbo/Dbo.h>

namespace tb::api
{

void LocalAuthClient::SignUp(
	const tb::models::dto::SignUpRequest& data,
	tb::models::dto::APICallback<tb::models::dto::SignUpResponse> callback
)
{
	tb::models::dto::APIResult<tb::models::dto::SignUpResponse> result;

	try
	{
		Wt::Dbo::Transaction trx{ *GetDatabaseSession() };

		int count = GetDatabaseSession()->query<int>("select count(*) from identity")
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
		auto identityPtr = GetDatabaseSession()->add(std::move(identity));

		std::string pwd_hash = tb::tools::Security::HashPassword(data.Password);
		credential->SetPasswordHash(pwd_hash);
		credential->SetIdentity(identityPtr);
		GetDatabaseSession()->add(std::move(credential));

		trx.commit();

		result.Success = true;
		result.Result.Email = data.Email;
	}
	catch (const Wt::Dbo::Exception& e)
	{
		result.Success = false;
		result.ErrorMessage = "Error while trying to write to the Database...";
		tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
		GetSessionContext()->Clear();
	}

	callback(result);
}

void LocalAuthClient::SignIn(
	const tb::models::dto::SignInRequest& data,
	tb::models::dto::APICallback<tb::models::dto::SignInResponse> callback
)
{
	// Resetting API Session Context
	GetSessionContext()->Clear();

	tb::models::dto::APIResult<tb::models::dto::SignInResponse> result;
	result.Success = false;
	result.ErrorMessage = "Invalid email or password."; // Default fallback error

	try
	{
		Wt::Dbo::Transaction trx{ *GetDatabaseSession()};

		auto identities = GetDatabaseSession()->find<tb::models::dbo::Identity>()
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
					GetSessionContext()->CurrentFinancialBookId = "";
					GetSessionContext()->Email = identity->GetEmail();
					GetSessionContext()->FirstName = identity->GetFirstName();
					GetSessionContext()->LastName = identity->GetLastName();
					GetSessionContext()->IdentityId = identity->GetId();

					result.Success = true;
					result.ErrorMessage = "";
					result.Result.Email = identity->GetEmail();
					result.Result.FirstName = identity->GetFirstName();
					result.Result.LastName = identity->GetLastName();
					result.Result.IdentityId = identity->GetId();

					tb::tools::log::GetApiLogger()->info("User {} logged in succesfully.", result.Result.IdentityId);
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

} // ns tb::api