#ifndef TB_CORE_DB_GENERIC_SESSION_HPP
#define TB_CORE_DB_GENERIC_SESSION_HPP

#include <filesystem>
#include <string>
#include <memory>

#include <wt/Dbo/Dbo.h>

namespace tb::core::db
{

class GenericSession
{
public:
	GenericSession() = default;

	virtual ~GenericSession() = default;

	GenericSession(const GenericSession&) = delete;
	GenericSession& operator=(const GenericSession&) = delete;
	GenericSession(GenericSession&&) = delete;
	GenericSession& operator=(GenericSession&&) = delete;

	/**
	 * @brief Opens or creates an encrypted SQLite3 database, verifies header decryption,
	 *        configures connection pragmas (WAL, foreign keys), maps DBO entities, and
	 *        executes pending schema migrations.
	 * @param dbPath Full or relative path to SQLite3 database file.
	 * @param hexKey256 64-character hexadecimal string encoding the 256-bit encryption key.
	 * @throws Wt::Dbo::Exception If database initialization, key verification, or migration fails.
	*/
	void Open(
		const std::filesystem::path& dbPath,
		const std::string& hexKey256
	);

	/**
	 * @brief Returns a Wt::Dbo::Session pointer to operate on the Database.
	 * @return Wt::Dbo::Session pointer.
	 */
	[[nodiscard]] const std::shared_ptr<Wt::Dbo::Session>& Session() noexcept;

protected:
	/**
	 * @brief Pure virtual method used by the derived class to apply the mappings between
	 * database tables and Wt::Dbo objects.
	 */
	virtual void MapClasses() = 0;

	/**
	 * @brief Pure virtual method used by the derived class to apply database migrations.
	 * @param currentVersion Version of the current applied schema.
	 * @return Version of the new schema.
	 */
	[[nodiscard]] virtual int ApplyMigrations(int currentVersion) = 0;

private:	
	/**
	 * @brief Fetch current schema version and calls GenericSession::ApplyMigrations, which returns the new version.
	 *        If the new version is greater than the current one, "PRAGMA version {VERSION}" is executed.
	 *        Otherwise, Wt::Dbo::Exception is thrown.
	 * @throws Wt::Dbo::Exception If new version is less than current version.
	 */
	void Migrate();


	std::shared_ptr<Wt::Dbo::Session> m_session;

}; // cl GenericSession

} // ns tb::core::db

#endifg