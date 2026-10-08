#ifndef TB_APP_MODELS_IDENTITY_HPP
#define TB_APP_MODELS_IDENTITY_HPP

#include <string>
#include <memory>

namespace tb::app::models::api
{

struct PasswordCredential;

struct Identity
{
	std::string Id;

	std::string Email;

	std::string FirstName;

	std::string LastName;

	std::weak_ptr<PasswordCredential> ToPasswordCredential;
};

struct PasswordCredential
{
	std::string Id;

	Identity ToIdentity;

	std::string PasswordHash;

	std::string PasswordAlgo;

	std::int64_t FailedAttempts;
};

struct SignUpRequest
{
	std::string Email;
	std::string Password;
	std::string FirstName;
	std::string LastName;
};

struct SignInRequest
{
	std::string Email;
	std::string Password;
};

struct SignInResponse
{
	std::string Email;
	std::string Id;
	std::string FirstName;
	std::string LastName;

	// Optional - Used only by RemoteSession
	std::string AccessToken{};
	std::string RefreshToken{};
};

struct SignUpResponse
{
	std::string Email;
	std::string Id;
};

}

#endif