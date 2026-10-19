#ifndef TB_APP_API_LOCAL_LOCAL_API_SERVICE
#define TB_APP_API_LOCAL_LOCAL_API_SERVICE

#include <tb/app/api/BaseApiService.hpp>

namespace Wt::Dbo { class Session; }

namespace tb::app::api
{

class LocalApiService : public tb::app::api::BaseApiService
{
public:
	LocalApiService();

private:
	std::shared_ptr<Wt::Dbo::Session> m_dbSession;

}; // cl LocalApiService

} // ns tb::app::api

#endif