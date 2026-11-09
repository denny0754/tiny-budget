 /*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-09 | Diego Vaccher | API-0000001-M | API Response model refactor
================================================================================
*/

#ifndef TB_MODELS_DTO_COMMON_HPP
#define TB_MODELS_DTO_COMMON_HPP

#include <string>
#include <vector>

namespace tb::models::dto
{

template<typename ResponseDataType>
class APIResponse
{
public:
	APIResponse(
		const std::vector<ResponseDataType>& data,
		unsigned int page = 0,
		bool error = false,
		const std::string& error_msg = std::string("")
	)
		: m_data(std::move(data)), m_page(page), m_error(error), m_errorMessage(std::move(error_msg))
	{

	}

	[[nodiscard]] bool Ok() const
	{
		return !m_error;
	}

	[[nodiscard]] const std::string& GetErrorMessage() const
	{
		return m_errorMessage;
	}

	[[nodiscard]] const std::vector<ResponseDataType>& GetData() const
	{
		return m_data;
	}

	[[nodiscard]] const std::size_t GetSize() const
	{
		return m_data.size();
	}

	[[nodiscard]] const unsigned int GetPage() const
	{
		return m_page;
	}

private:
	std::string m_errorMessage;

	bool m_error;

	unsigned int m_page;

	std::vector<ResponseDataType> m_data;
}; // cl APIResponse

} // ns tb::models::dto

#endif