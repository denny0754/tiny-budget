/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#ifndef TB_MODELS_DTO_AUTH_HPP
#define TB_MODELS_DTO_AUTH_HPP

#include <tb/models/dto/Common.hpp>

#include <string>

namespace tb::models::dto
{

struct SignUpRequest
{
	std::string Email;

	std::string Password;

	std::string FirstName;

	std::string LastName;

}; // st SignUpRequest

struct SignUpResponseData
{
	std::string IdentityGuid;

	std::string Email;

}; // st SignUpResponseData

struct SignInRequest
{
	std::string Email;

	std::string Password;

}; // st SignInRequest

struct SignInResponseData
{
	std::string IdentityGuid;

	std::string Email;
}; // st SignInResponseData

// Template Initialization
using SignInResponse = tb::models::dto::APIResponse<SignInResponseData>;
using SignUpResponse = tb::models::dto::APIResponse<SignUpResponseData>;

} // ns tb::models::dto

#endif