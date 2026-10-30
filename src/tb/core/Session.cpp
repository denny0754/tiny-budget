#include <tb/core/Session.hpp>
#include <tb/api/Service.hpp>
#include <tb/events/ui/PushGlobalComponentEvent.hpp>
#include <tb/ui/global/SideMenu.hpp>

namespace tb::core
{

Session::Session(std::shared_ptr<tb::events::EventDispatcher> dispatcher)
	: m_eventDispatcher(dispatcher)
{
	m_sessionContext = std::make_shared<tb::core::SessionContext>();

	m_service = std::make_shared<tb::api::Service>(m_sessionContext);

    m_eventDispatcher->Subscribe<tb::events::IdentitySignedInEvent>(TB_BIND_EVENT_FN(OnIdentitySignedIn));
    m_eventDispatcher->Subscribe<tb::events::IdentitySignedOutEvent>(TB_BIND_EVENT_FN(OnIdentitySignedOut));
}

void Session::OnIdentitySignedIn(const tb::events::IdentitySignedInEvent& event)
{
    m_eventDispatcher->Enqueue<tb::events::PushGlobalComponentEvent>(
        std::make_unique<tb::events::PushGlobalComponentEvent>(
            [](const std::shared_ptr<tb::events::EventDispatcher>& dispatcher,
                const std::shared_ptr<tb::core::Session>& session) -> std::unique_ptr<tb::ui::SideMenu> {
                    return std::make_unique<tb::ui::SideMenu>(dispatcher, session);
            }
        )
    );
}

void Session::OnIdentitySignedOut(const tb::events::IdentitySignedOutEvent& event)
{

}

} // ns tb::core