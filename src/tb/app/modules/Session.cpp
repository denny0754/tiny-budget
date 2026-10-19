#include <tb/app/modules/Session.hpp>

#include <tb/core/events/PushModuleEvent.hpp>
#include <tb/app/events/PushGlobalComponentEvent.hpp>
#include <tb/app/ui/AuthenticationForm.hpp>
#include <tb/app/ui/MenuBar.hpp>
#include <tb/app/api/local/LocalApiService.hpp>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <Wt/Dbo/Dbo.h>

namespace tb::app::modules
{

void Session::OnInit()
{
    m_sessionCtx = std::make_shared<SessionContext>();

    // Initializing the default Application Logger:
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.push_back(
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./logs/session.log", 52428800U, 7, false)
    );
    logSinks.push_back(
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
    );
    m_sessionCtx->logger = std::make_shared<spdlog::logger>("Session", begin(logSinks), end(logSinks));
    m_sessionCtx->logger->set_level(spdlog::level::level_enum::trace);
    m_sessionCtx->logger->set_pattern("[%Y-%m-%d %H:%M:%S] %n - %^%l%$: %v");

    m_sessionCtx->eventDispatcher = std::make_shared<EventDispatcher>();

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

    m_sessionCtx->apiService = std::make_shared<tb::app::api::LocalApiService>();

    m_sessionCtx->eventDispatcher->Subscribe<tb::app::events::IdentitySignedInEvent>(
        TB_APP_BIND_EVENT_FN(OnIdentitySignedIn)
    );
    m_sessionCtx->eventDispatcher->Subscribe<tb::app::events::IdentitySignedOutEvent>(
        TB_APP_BIND_EVENT_FN(OnIdentitySignedOut)
    );
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
    m_sessionCtx->logger->info("User with ID `{}` logged in succesfully.",
        event.GetIdentityId()
    );

    m_sessionCtx->sessionData.email = event.GetEmail();
    m_sessionCtx->sessionData.firstName = event.GetFirstName();
    m_sessionCtx->sessionData.lastName = event.GetLastName();
    m_sessionCtx->sessionData.identityId = event.GetIdentityId();

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