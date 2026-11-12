#include <tb/core/Session.hpp>
#include <tb/api/Service.hpp>
#include <tb/events/ui/PushGlobalComponentEvent.hpp>
#include <tb/ui/global/SideMenu.hpp>
#include <tb/tools/Logging.hpp>
#include <tb/api/BookClient.hpp>

#include <chrono>
#include <thread>

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
            [](tb::events::ConstEventDispatcherRef dispatcher, tb::core::ConstSessionRef session, std::unique_ptr<tb::ui::ComponentData> data) -> std::unique_ptr<tb::ui::SideMenu> {
                    return std::make_unique<tb::ui::SideMenu>(dispatcher, session, std::move(data));
            }
        )
    );
    GetService()->GetSessionContext()->IdentityId = event.GetIdentityId();
    tb::tools::log::GetSessionLogger()->info("Idenity Signed In: {}", GetService()->GetSessionContext()->IdentityId);

    std::thread(
        [this]() {
            auto response = GetService()->GetClient<tb::api::BookClient>()->GetAny();
            if (response.Ok())
            {
                GetService()->GetSessionContext()->ActiveBooks.clear();
                auto responseData = response.GetData();
                for (auto book : responseData)
                {
                    tb::models::bdo::Book bookData = tb::models::bdo::Book(
                        book.Guid,
                        std::chrono::system_clock::now(),
                        std::chrono::system_clock::now(),
                        GetService()->GetSessionContext()->IdentityId,
                        book.Name,
                        book.Description,
                        book.CurrencyGuid
                    );
                    GetService()->GetSessionContext()->ActiveBooks.push_back(bookData);
                }
            }
        }
    ).detach();
}

void Session::OnIdentitySignedOut(const tb::events::IdentitySignedOutEvent& event)
{

}

} // ns tb::core