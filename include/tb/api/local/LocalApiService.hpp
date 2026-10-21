#ifndef TB_API_LOCAL_LOCAL_API_SERVICE_HPP
#define TB_API_LOCAL_LOCAL_API_SERVICE_HPP

#include <tb/api/core/BaseApiService.hpp>

namespace Wt::Dbo { class Session; }

namespace tb::api
{

class LocalApiService : public tb::api::BaseApiService
{
public:
	LocalApiService();

private:
	std::shared_ptr<Wt::Dbo::Session> m_dbSession;

}; // cl LocalApiService

} // ns tb::app::api

#endif