#include "GenericSession.hpp"

#include <Wt/Dbo/backend/Sqlite3.h>

namespace tb::core::db
{

void GenericSession::Open(
	const std::filesystem::path& dbPath,
	const std::string& hexKey256
)
{
	// Ensuring that all paths exists
	std::filesystem::create_directories(dbPath.parent_path());

	bool error = false;

	try
	{
		std::unique_ptr<Wt::Dbo::backend::Sqlite3> sqliteBackend = std::make_unique<Wt::Dbo::backend::Sqlite3>(dbPath);
		sqliteBackend->executeSql(std::format("PRAGMA KEY {}", hexKey256));
		sqliteBackend->executeSql("SELECT count(*) FROM sqlite_master;");
		sqliteBackend->executeSql("PRAGMA journal_mode = WAL;");
		sqliteBackend->executeSql("PRAGMA foreign_keys = ON;");

		m_session = std::make_shared<Wt::Dbo::Session>();
		m_session->setConnection(std::move(sqliteBackend));
	}
	catch (Wt::Dbo::Exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		error = true;
	}

	if (!error)
	{
		MapClasses();
		Migrate();
	}
}

const std::shared_ptr<Wt::Dbo::Session>& GenericSession::Session() noexcept
{
	return m_session;
}

void GenericSession::Migrate()
{
	Wt::Dbo::Transaction tx(m_session);

	const int currentVersion = m_session.query<int>("PRAGMA user_version").resultValue();
	const int targetVersion = ApplyMigrations(currentVersion);

	if (targetVersion < currentVersion)
	{
		throw Wt::Dbo::Exception(
			std::format(
				"Database schema version ({}) is newer than application schema version ({}).",
				currentVersion,
				targetVersion
			)
		);
	}

	if (targetVersion > currentVersion)
	{
		m_session.execute(std::format("PRAGMA user_version = {};", targetVersion));
	}

	tx.commit();
}

} // ns tb::core::db