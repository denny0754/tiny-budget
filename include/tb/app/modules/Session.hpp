#ifndef TB_APP_MODULES_SESSION_HPP
#define TB_APP_MODULES_SESSION_HPP

#include <memory> 

#include <tb/core/BaseModule.hpp>
#include <tb/app/SessionContext.hpp>
#include <tb/app/ui/UIController.hpp>
#include <tb/app/events/IdentitySignedIn.hpp>
#include <tb/app/events/IdentitySignedOut.hpp>

namespace tb::app::modules
{

class Session : public core::BaseModule
{
public:

	void OnInit() override;

	void OnRender() override;

	void OnUpdate(double deltaTime = 0.f) override;

	void OnShutdown() override;

private:
	void OnIdentitySignedIn(const tb::app::events::IdentitySignedIn& event);

	void OnIdentitySignedOut(const tb::app::events::IdentitySignedOut& event);

private:
	std::shared_ptr<SessionContext> m_sessionCtx;

	std::unique_ptr<ui::UIController> m_uiController;
}; // cl Session

} // ns tb::app::modules

#endif