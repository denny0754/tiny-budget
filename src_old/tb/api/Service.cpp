/*
=================================================================================
 CHANGE LOG
=================================================================================
 Date       | Author        | Task ID        | Description
------------+---------------+----------------+-----------------------------------
 2026-11-14 | Diego Vaccher | CORE-0000011-M | Fix Data Model references
=================================================================================
*/

#include <tb/api/Service.hpp>
#include <tb/api/AuthClient.hpp>
#include <tb/api/CurrencyClient.hpp>
#include <tb/api/BookClient.hpp>
#include <tb/models/dbo/Dbo.hpp>
#include <tb/tools/Security.hpp>
#include <tb/tools/Logging.hpp>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>

#include <filesystem>

namespace tb::api
{

Service::Service(std::shared_ptr<tb::core::SessionContext> ctx)
{
    m_sessionContext = ctx;
    m_dbSession = std::make_shared<Wt::Dbo::Session>();

    std::filesystem::create_directory("./data");

    auto sqliteBackend = std::make_unique<Wt::Dbo::backend::Sqlite3>("data/db.sqlite");
    m_dbSession->setConnection(std::move(sqliteBackend));

    m_dbSession->mapClass<tb::models::dbo::Identity>("identity");
    m_dbSession->mapClass<tb::models::dbo::PasswordCredential>("password_credential");
    m_dbSession->mapClass<tb::models::dbo::Book>("book");
    m_dbSession->mapClass<tb::models::dbo::Partner>("partner");
    m_dbSession->mapClass<tb::models::dbo::Account>("account");
    m_dbSession->mapClass<tb::models::dbo::Transaction>("transaction");
    m_dbSession->mapClass<tb::models::dbo::TransactionItem>("transaction_item");
    m_dbSession->mapClass<tb::models::dbo::Product>("product");
    m_dbSession->mapClass<tb::models::dbo::BookStatus>("book_status");
    m_dbSession->mapClass<tb::models::dbo::Currency>("currency");
    m_dbSession->mapClass<tb::models::dbo::AccountType>("account_type");

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

	RegisterClient<tb::api::AuthClient>();
    RegisterClient<tb::api::CurrencyClient>();
    RegisterClient<tb::api::BookClient>();    
}

Service::~Service()
{

}

} // ns tb::api