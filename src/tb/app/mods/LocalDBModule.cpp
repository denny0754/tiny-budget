#include <tb/app/mods/LocalDBModule.hpp>

#include <Wt/Dbo/backend/Sqlite3.h>

#include <tb/app/models/Identity.hpp>
#include <tb/app/models/PasswordCredential.hpp>

namespace tb::app::mods
{

void LocalDBModule::OnInit()
{
    auto sqlite3Session = std::make_unique<Wt::Dbo::backend::Sqlite3>(":memory:");

    m_dbSession.setConnection(std::move(sqlite3Session));

    m_dbSession.mapClass<tb::app::models::Identity>("identity");
    m_dbSession.mapClass<tb::app::models::PasswordCredential>("password_credential");
}

void LocalDBModule::OnUpdate(double deltaTime)
{

}

void LocalDBModule::OnShutdown()
{

}

void LocalDBModule::OnDatabaseOperation(const tb::app::events::DatabaseOperationEvent& event)
{
    try {
        Wt::Dbo::Transaction transaction(m_dbSession);
        if (event.Payload) {
            event.Payload(m_dbSession);
        }
        
            transaction.commit();
        }
    catch (const std::exception& ex) {
            // Log database error
    }
}

}