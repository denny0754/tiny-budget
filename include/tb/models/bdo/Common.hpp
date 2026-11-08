#ifndef TB_MODELS_BDO_COMMON_HPP
#define TB_MODELS_BDO_COMMON_HPP

#include <string>
#include <chrono>

namespace tb::models::bdo
{

class BaseDataObject
{
public:
	BaseDataObject(
		const std::string& guid,
		const std::chrono::system_clock::time_point& created_on,
		const std::chrono::system_clock::time_point& updated_on
	);

	const std::string& GetGuid() const;

	const std::chrono::system_clock::time_point& GetCreatedOn() const;

	const std::chrono::system_clock::time_point& GetUpdatedOn() const;

private:
	std::string m_guid;
	std::chrono::system_clock::time_point m_createdOn;
	std::chrono::system_clock::time_point m_updatedOn;

}; // cl BaseDataObject

} // tb::models::bdo

#endif 