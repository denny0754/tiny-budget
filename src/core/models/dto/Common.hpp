#ifndef TB_CORE_MODELS_DTO_COMMON_HPP
#define TB_CORE_MODELS_DTO_COMMON_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace tb::dto
{

template<class DataObject>
struct DataResult
{
	DataObject data{};

	bool error{ false };

	std::string error_message{};
}; // st DataResult

/**
 * @brief Used for operations that do
 *        not output a result.
 */
using EmptyDataResult = DataResult<void>;

template<class DataObject>
struct SlicedDataResult
{
	std::vector<DataObject> data{};

	std::uint32_t offset{ 0 };

	bool error{ false };

	std::string error_message;
}; // st SlicedDataResult

struct DataCountResult
{
	std::uint64_t count{ 0 };

	bool error{ false };

	std::string error_message{};
}; // st DataCountResult

} // ns tb::dto

#endif