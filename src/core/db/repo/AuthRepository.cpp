#include "core/db/repo/AuthRepository.hpp"
#include "core/models/dbo/Security.hpp"

#include <string>

#include <sodium.h>
#include <Wt/Dbo/Dbo.h>

namespace tb::db
{

AuthRepository::AuthRepository(const std::shared_ptr<Wt::Dbo::Session>& session)
	: tb::db::Repository(session)
{

}

tb::dto::DataResult<tb::dto::Identity> AuthRepository::SignUp(const tb::dto::SignUpCommand& data)
{
	bool error{ false };
	std::string errorMsg{};
	tb::dto::DataResult<tb::dto::Identity> result;

	try
	{
		auto dbSession = Session();
		Wt::Dbo::Transaction trx{ *dbSession };

		int count = dbSession->query<int>("SELECT COUNT(*) FROM identity")
			.where("email = ?")
			.bind(data.email);

		if (count > 0)
		{
			error = true;
			errorMsg = "An account with this email address already exists!.";
		}
		else
		{
			auto identity = std::make_unique<tb::dbo::Identity>();
			auto credential = std::make_unique<tb::dbo::PasswordCredential>();

			identity->SetEmail(data.email);
			identity->SetFirstName(data.first_name);
			identity->SetLastName(data.last_name);
			auto identityPtr = dbSession->add(std::move(identity));

			std::string passwordHash = HashPassword(data.password);
			credential->SetPasswordHash(passwordHash);
			credential->SetIdentity(identityPtr);
			dbSession->add(std::move(credential));

			trx.commit();

			result.data.email = data.email;
			result.data.first_name = data.first_name;
			result.data.last_name = data.last_name;
			result.data.guid = identityPtr->GetEmail();
		}
	}
	catch (const Wt::Dbo::Exception&)
	{
		error = true;
		errorMsg = "Error while processing sign-up.";
	}
	catch (const std::runtime_error&)
	{
		error = true;
		errorMsg = "An unknown error occured during sign-up. Try again later.";
	}

	if (error)
	{
		result.data = {};
		result.error = error;
		result.error_message = errorMsg;
	}

	return result;
}

tb::dto::DataResult<tb::dto::Identity> AuthRepository::SignIn(const tb::dto::SignInCommand& data)
{
	bool error{ false };
	std::string errorMsg{};
	tb::dto::DataResult<tb::dto::Identity> result;

	try
	{
		auto dbSession = Session();
		Wt::Dbo::Transaction trx{ *dbSession };

		auto identities = dbSession->find<tb::dbo::Identity>()
			.where("email = ?")
			.bind(data.email)
			.resultList();

		if (!identities.empty())
		{
			auto identity = identities.front();
			auto credentialPtr = identity->GetPasswordCredential();

			if (credentialPtr)
			{
				std::string stored_hash = credentialPtr->GetPasswordHash();

				bool isPasswordValid = VerifyPasswordHash(
					data.password,
					stored_hash
				);

				if (isPasswordValid)
				{
					error = false;
					errorMsg = std::string("");
					result.data.guid = identity->GetId();
					result.data.email = identity->GetEmail();
					result.data.first_name = identity->GetFirstName();
					result.data.last_name = identity->GetLastName();
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
		result.data = {};
		result.error = error;
		result.error_message = errorMsg;
	}

	return result;
}

std::string AuthRepository::HashPassword(const std::string& password) const
{
	if (static bool initialized = false; !initialized)
	{
		if (sodium_init() < 0)
		{
			throw std::runtime_error("Fatal: Failed to initialize libsodium environment.");
		}
		initialized = true;
	}

	// Buffer required by libsodium for stored password strings
	char hashedPasswordBuf[crypto_pwhash_STRBYTES];

	if (crypto_pwhash_str(
		hashedPasswordBuf,
		password.c_str(),
		password.length(),
		crypto_pwhash_OPSLIMIT_MODERATE,
		crypto_pwhash_MEMLIMIT_MODERATE
	) != 0)
	{
		throw std::runtime_error("Fatal: Out of memory or system error while hashing password.");
	}

	return std::string(hashedPasswordBuf);
}

bool AuthRepository::VerifyPasswordHash(const std::string& password, const std::string& hash) const
{
	if (static bool initialized = false; !initialized)
	{
		if (sodium_init() < 0)
		{
			throw std::runtime_error("Fatal: Failed to initialize libsodium environment.");
		}
		initialized = true;
	}

	if (hash.empty())
	{
		return false;
	}

	return (crypto_pwhash_str_verify(
		hash.c_str(),
		password.c_str(),
		password.length()
	) == 0);
}

} // ns tb::db