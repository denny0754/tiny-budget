#include <tb/app/modules/Session.hpp>

#include <tb/core/events/PushModuleEvent.hpp>
#include <tb/app/events/PushGlobalComponentEvent.hpp>
#include <tb/app/ui/AuthenticationForm.hpp>
#include <tb/app/ui/MenuBar.hpp>
#include <tb/api/local/LocalApiService.hpp>
#include <tb/tools/Logging.hpp>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <Wt/Dbo/Dbo.h>

namespace tb::app::modules
{

void Session::OnInit()
{
    m_sessionCtx = std::make_shared<SessionContext>();

    m_sessionCtx->eventDispatcher = std::make_shared<EventDispatcher>();

    tb::tools::log::GetSessionLogger()->info("Session Manager is being initialized.");

    m_uiController = std::make_unique<tb::app::ui::Controller>(m_sessionCtx);

    m_uiController->Init();

    m_sessionCtx->eventDispatcher->QueueEvent<events::PushGlobalComponentEvent>(
        events::PushGlobalComponentEvent(
            []() -> std::unique_ptr<tb::app::ui::AuthenticationForm>
            {
                return std::make_unique<tb::app::ui::AuthenticationForm>();
            }
        )
    );

    m_sessionCtx->apiService = std::make_shared<tb::api::LocalApiService>();

    m_sessionCtx->eventDispatcher->Subscribe<tb::app::events::IdentitySignedInEvent>(
        TB_APP_BIND_EVENT_FN(OnIdentitySignedIn)
    );
    m_sessionCtx->eventDispatcher->Subscribe<tb::app::events::IdentitySignedOutEvent>(
        TB_APP_BIND_EVENT_FN(OnIdentitySignedOut)
    );

    tb::tools::log::GetSessionLogger()->info("Session Manager succesfully initialized.");
}

void Session::OnRender()
{
    m_uiController->Render();
}

void Session::OnUpdate(double deltaTime)
{
    m_uiController->Update();
    m_sessionCtx->eventDispatcher->DispatchQueued();
}

void Session::OnShutdown()
{
    m_uiController->Shutdown();
}

void Session::OnIdentitySignedIn(const tb::app::events::IdentitySignedInEvent& event)
{
    // Initialize Menu Bar, User Information, maybe a Financial Book Selector.
    tb::tools::log::GetSessionLogger()->info("User with ID `{}` logged in succesfully.",
        event.GetIdentityId()
    );

    m_sessionCtx->eventDispatcher->QueueEvent<tb::app::events::PushGlobalComponentEvent>(
        tb::app::events::PushGlobalComponentEvent(
            []() -> std::unique_ptr<tb::app::ui::MenuBar> {
                return std::make_unique<tb::app::ui::MenuBar>();
            }
        )
    );

    event.Handled = true;
}

void Session::OnIdentitySignedOut(const tb::app::events::IdentitySignedOutEvent& event)
{
    // De-initialize everything the user opened and re-open the AuthenticationForm UI component.
}

} // ns tb::app::mods