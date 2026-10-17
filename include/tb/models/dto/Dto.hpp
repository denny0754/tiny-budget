#ifndef TB_MODELS_DTO_HPP
#define TB_MODELS_DTO_HPP

namespace tb::models::dto
{

template<typename T>
struct APIResult
{
	std::string ErrorMessage{};
	bool Success;

	T Result;
}; // st APIResult

struct SignUpRequest
{
	std::string Email;

	std::string Password;

	std::string FirstName;

	std::string LastName;

}; // st SignUpRequest

struct SignUpResponse
{
	std::string IdentityId;

	std::string Email;

}; // st SignUpResponse

struct SignInRequest
{
	std::string Email;

	std::string Password;

}; // st SignInRequest

struct SignInResponse
{
	//TODO: When RemoteAPIProvider will be available, JWT members should be added
	//		such as "AccessToken", "RefreshToken", "IAT", "EXP", etc...
	//		As of now, these are the one necessary to allow a local session.
	std::string IdentityId;

	std::string Email;

	std::string FirstName;

	std::string LastName;
}; // st SignInResponse

struct CreateFinancialBookRequest
{

	std::string Name;

	std::string DefaultCurrency;

}; // st CreateFinancialBookRequest

struct CreateFinancialBookResponse
{
	std::string FinancialBookId;
};

} // ns tb::models::dto

#endif