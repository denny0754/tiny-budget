#ifndef TB_CORE_DB_REPO_REPOSITORY
#define TB_CORE_DB_REPO_REPOSITORY

namespace Wt::Dbo { class Session; };

namespace tb::db
{

class Repository
{
public:
	explicit Repository(const Wt::Dbo::Session& session)
		: m_session(session)
	{

	}
	virtual ~Repository() = default;

protected:
	const Wt::Dbo::Session& Session() const
	{
		return m_session;
	}

private:
	const Wt::Dbo::Session& m_session;
}; // cl Repository

} // ns tb::db

#endif