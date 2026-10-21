#ifndef TB_API_LOCAL_LOCAL_BASE_CLIENT_HPP
#define TB_API_LOCAL_LOCAL_BASE_CLIENT_HPP

#include <tb/api/core/BaseClient.hpp>

namespace Wt::Dbo { class Session; }
namespace tb::app::api { class LocalApiService; }

namespace tb::api
{

class LocalBaseClient : public tb::api::BaseClient
{
public:
	explicit LocalBaseClient(std::shared_ptr<tb::api::SessionContext> ctx, std::shared_ptr<Wt::Dbo::Session> db)
		: BaseClient(ctx), m_dbSession(db)
	{

	}

protected:
	const std::shared_ptr<Wt::Dbo::Session>& GetDatabaseSession() const
	{
		return m_dbSession;
	}

private:
	std::shared_ptr<Wt::Dbo::Session> m_dbSession;

}; // cl LocalBaseClient

} // ns tb::api

#endif