#ifndef TB_APP_MODULES_SESSION_HPP
#define TB_APP_MODULES_SESSION_HPP

#include <memory> 

#include <tb/core/BaseModule.hpp>
#include <tb/app/ServiceRegistry.hpp>
#include <tb/app/ui/Controller.hpp>
#include <tb/app/events/IdentitySignedInEvent.hpp>
#include <tb/app/events/IdentitySignedOutEvent.hpp>

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
	void OnIdentitySignedIn(const tb::app::events::IdentitySignedInEvent& event);

	void OnIdentitySignedOut(const tb::app::events::IdentitySignedOutEvent& event);

private:
	std::shared_ptr<tb::app::ServiceRegistry> m_serviceReg;

	std::unique_ptr<tb::app::ui::Controller> m_uiController;
}; // cl Session

} // ns tb::app::modules

#endif