#ifndef TB_APP_MODS_DB_MODULE_HPP
#define TB_APP_MODS_DB_MODULE_HPP

#include <Wt/Dbo/Session.h>

#include <tb/core/mod/Module.hpp>
#include <tb/app/events/DatabaseOperationEvent.hpp>

namespace tb::app::mods
{

class DatabaseModule : public tb::core::mod::Module
{
public:
    void OnInit() override;

    void OnRender() override { return; }

    void OnUpdate(double deltaTime = .0f) override;

    void OnShutdown() override;
private:
    void OnDatabaseOperation(const tb::app::events::DatabaseOperationEvent& event);

private:
    Wt::Dbo::Session m_dbSession;
};
    
} // ns tb::app::mods

#endif