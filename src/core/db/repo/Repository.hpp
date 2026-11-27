#ifndef TB_CORE_DB_REPO_REPOSITORY
#define TB_CORE_DB_REPO_REPOSITORY

#include <memory>

namespace Wt::Dbo { class Session; };

namespace tb::db
{

class Repository
{
public:
	explicit Repository(const std::shared_ptr<Wt::Dbo::Session>& session)
		: m_session(session)
	{

	}
	virtual ~Repository() = default;

protected:
	const std::shared_ptr<Wt::Dbo::Session>& Session() const
	{
		return m_session;
	}

private:
	std::shared_ptr<Wt::Dbo::Session> m_session;
}; // cl Repository

} // ns tb::db

#endif