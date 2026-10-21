#include <tb/api/local/LocalApiService.hpp>
#include <tb/api/local/LocalAuthClient.hpp>
#include <tb/models/dbo/Dbo.hpp>
#include <tb/tools/Security.hpp>
#include <tb/tools/Logging.hpp>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>

#include <filesystem>

namespace tb::api
{

LocalApiService::LocalApiService()
{
	tb::tools::log::GetApiLogger()->info("Local API Service is being initialized.");

	m_dbSession = std::make_shared<Wt::Dbo::Session>();

	std::filesystem::create_directory("./data");

	auto sqliteBackend = std::make_unique<Wt::Dbo::backend::Sqlite3>("data/db.sqlite");
	m_dbSession->setConnection(std::move(sqliteBackend));

	m_dbSession->mapClass<tb::models::dbo::Identity>("identity");
	m_dbSession->mapClass<tb::models::dbo::PasswordCredential>("password_credential");
	m_dbSession->mapClass<tb::models::dbo::FinancialBook>("financial_book");
	m_dbSession->mapClass<tb::models::dbo::Partner>("partner");
	m_dbSession->mapClass<tb::models::dbo::PartnerAddress>("partner_address");
	m_dbSession->mapClass<tb::models::dbo::PartnerCommunication>("partner_communication");
	m_dbSession->mapClass<tb::models::dbo::Account>("account");
	m_dbSession->mapClass<tb::models::dbo::Transaction>("transaction");
	m_dbSession->mapClass<tb::models::dbo::TransactionItem>("transaction_item");
	m_dbSession->mapClass<tb::models::dbo::Product>("product");
	m_dbSession->mapClass<tb::models::dbo::CodeList>("code_list");

    try
    {
        bool tablesExist = false;

        {
            Wt::Dbo::Transaction checkTrx{ *m_dbSession };
            int tableCount = m_dbSession->query<int>(
                "SELECT COUNT(1) FROM sqlite_master WHERE type='table' AND name='identity'"
            );
            checkTrx.commit();
            tablesExist = (tableCount > 0);
        }

        if (!tablesExist)
        {
            tb::tools::log::GetApiLogger()->info("Database tables not found. Creating schema...");
            Wt::Dbo::Transaction createTrx{ *m_dbSession };
            m_dbSession->createTables();
            createTrx.commit();
            tb::tools::log::GetApiLogger()->info("Database schema initialized successfully.");
        }
        else
        {
            tb::tools::log::GetApiLogger()->info("Database schema already exists. Skipping table creation.");
        }
    }
    catch (const Wt::Dbo::Exception& e)
    {
        tb::tools::log::GetApiLogger()->critical("Error while initializing SQLite3 Backend...");
        tb::tools::log::GetApiLogger()->error("Wt::Dbo Exception: {}", e.what());
    }

	m_authService = std::make_unique<tb::api::LocalAuthClient>(m_apiCtx, m_dbSession);
}


} // ns tb::api