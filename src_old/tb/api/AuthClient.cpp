/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#include <tb/api/AuthClient.hpp>
#include <tb/models/dbo/Dbo.hpp>
#include <tb/tools/Security.hpp>
#include <tb/tools/Logging.hpp>

#include <Wt/Dbo/Dbo.h>

namespace tb::api
{

tb::models::dto::SignUpResponse AuthClient::SignUp(
	const tb::models::dto::SignUpRequest& data
)
{
	bool error{ false };
	std::string errorMsg{ "Invalid email or password." };
	tb::models::dto::SignUpResponseData responseData{};

	try
	{
		auto dbSession = GetDbSession();
		Wt::Dbo::Transaction trx{ *dbSession };

		int count = dbSession->query<int>("select count(*) from identity")
			.where("email = ?")
			.bind(data.Email);

		if (count > 0)
		{
			error = true;
			errorMsg = "An account with this email address already exists.";
		}
		else
		{
			auto identity = std::make_unique<tb::models::dbo::Identity>();
			auto credential = std::make_unique<tb::models::dbo::PasswordCredential>();

			auto currentDateTime = Wt::WDateTime::currentDateTime();
			identity->SetFirstName(data.FirstName);
			identity->SetLastName(data.LastName);
			identity->SetEmail(data.Email);
			auto identityPtr = dbSession->add(std::move(identity));

			std::string pwd_hash = tb::tools::Security::HashPassword(data.Password);
			credential->SetPasswordHash(pwd_hash);
			credential->SetIdentity(identityPtr);
			dbSession->add(std::move(credential));

			trx.commit();

			error = false;
			responseData.Email = data.Email;
			responseData.IdentityGuid = identityPtr.id();
		}
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error while processing sign-in.";
	}

	if (error)
	{
		responseData = tb::models::dto::SignUpResponseData();
	}

	return tb::models::dto::SignUpResponse({ responseData }, 0, error, errorMsg);
}

tb::models::dto::SignInResponse AuthClient::SignIn(
	const tb::models::dto::SignInRequest& data
)
{
	bool error{ false };
	std::string errorMsg{ "Invalid email or password." };
	tb::models::dto::SignInResponseData responseData{};
	
	try
	{
		auto dbSession = GetDbSession();
		Wt::Dbo::Transaction trx{ *dbSession };

		auto identities = dbSession->find<tb::models::dbo::Identity>()
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
					error = false;
					errorMsg = std::string("");
					responseData.IdentityGuid = identity->GetId();
					responseData.Email = identity->GetEmail();
					tb::tools::log::GetApiLogger()->info("User {} logged in succesfully.", identity->GetId());
				}
			}
		}
	}
	catch (const Wt::Dbo::Exception& e)
	{
		error = true;
		errorMsg = "Database error while processing sign-in.";
	}

	if (error)
	{
		responseData = tb::models::dto::SignInResponseData();
	}

	return tb::models::dto::SignInResponse({ responseData }, 0, error, errorMsg);
}

} // ns tb::api