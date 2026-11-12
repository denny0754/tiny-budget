#include <tb/models/bdo/Common.hpp>

namespace tb::models::bdo
{

BaseDataObject::BaseDataObject(
	const std::string& guid,
	const std::chrono::system_clock::time_point& created_on,
	const std::chrono::system_clock::time_point& updated_on
)
	: m_guid(guid), m_createdOn(created_on), m_updatedOn(updated_on)
{

}

const std::string& BaseDataObject::GetGuid() const
{
	return m_guid;
}

const std::chrono::system_clock::time_point& BaseDataObject::GetCreatedOn() const
{
	return m_createdOn;
}

const std::chrono::system_clock::time_point& BaseDataObject::GetUpdatedOn() const
{
	return m_updatedOn;
}

} // ns tb::models::bdo